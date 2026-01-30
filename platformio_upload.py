# Allows PlatformIO to upload directly to ElegantOTA
#
# To use:
# - copy this script into the same folder as your platformio.ini
# - set the following for your project in platformio.ini:
#
# extra_scripts = platformio_upload.py
# upload_protocol = custom
# custom_upload_url = <your upload URL> (optional)
# custom_username = <ElegantOTA username> (optional)
# custom_password = <ElgantOTA password> (optional)
#
# If custom_upload_url is not specified in platformio.ini, you must define a
# hostname in src/config.h using:
# #define HOSTNAME "<your hostname>"
# Username and password can similarly be specified using:
# #define OTA_USER "<ElegantOTA username>"
# #define OTA_PASS "<ElegantOTA password>"
# 
# An example of an upload URL:
#                custom_upload_url = http://192.168.1.123/update 
# also possible: custom_upload_url = http://domainname/update

import sys
import requests
import hashlib
from urllib.parse import urlparse
import time
from requests.auth import HTTPDigestAuth
Import("env")

try:
    from requests_toolbelt import MultipartEncoder, MultipartEncoderMonitor
    from tqdm import tqdm
except ImportError:
    env.Execute("$PYTHONEXE -m pip install requests_toolbelt")
    env.Execute("$PYTHONEXE -m pip install tqdm")
    from requests_toolbelt import MultipartEncoder, MultipartEncoderMonitor
    from tqdm import tqdm

def on_upload(source, target, env):
    firmware_path = str(source[0])

    auth = None
    upload_url_compatibility = None
    username = None
    password = None

    # Attempt to get credentials and hostname from config header
    try:
        with open(env['PROJECT_SRC_DIR'] + '/config.h', 'r') as f:
            for line in f.readlines():
                if 'HOSTNAME' in line:
                    upload_url_compatibility = 'http://' + line.split('"')[1] + '/update'
                if 'OTA_USER' in line:
                    username = line.split('"')[1]
                if 'OTA_PASS' in line:
                    password = line.split('"')[1]
    except:
        pass

    try:
        upload_url_compatibility = env.GetProjectOption('custom_upload_url')
        username = env.GetProjectOption('custom_username')
        password = env.GetProjectOption('custom_password')
    except:
        pass

    if upload_url_compatibility is None:
        return "No upload URL or hostname specified."
    upload_url = upload_url_compatibility.replace("/update", "")

    with open(firmware_path, 'rb') as firmware:
        md5 = hashlib.md5(firmware.read()).hexdigest()

        parsed_url = urlparse(upload_url)
        host_ip = parsed_url.netloc

        is_spiffs = source[0].name == "spiffs.bin"
        file_type = "fs" if is_spiffs else "fr"

        # execute GET request
        start_url = f"{upload_url}/ota/start?mode={file_type}&hash={md5}"

        start_headers = {
            'Host': host_ip,
            'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/118.0',
            'Accept': '*/*',
            'Accept-Language': 'de,en-US;q=0.7,en;q=0.3',
            'Accept-Encoding': 'gzip, deflate',
            'Referer': f'{upload_url}/update',
            'Connection': 'keep-alive'
            }
        
        try:
            checkAuthResponse = requests.get(f"{upload_url_compatibility}/update")
        except Exception as e:
            return 'Error checking auth: ' + repr(e)
        
        if checkAuthResponse.status_code == 401:
            if username is None or password is None:
                return "Authentication required, but no credentials provided."
            print("Serverconfiguration: authentication needed.")
            auth = HTTPDigestAuth(username, password)
            try:
                doUpdateAuth = requests.get(start_url, headers=start_headers, auth=auth)
            except Exception as e:
                return 'Error while authenticating: ' + repr(e)

            if doUpdateAuth.status_code != 200:
                return "Authentication failed " + str(doUpdateAuth.status_code)
            print("Authentication successful")
        else:
            auth = None
            print("Serverconfiguration: authentication not needed.")
            try:
                doUpdate = requests.get(start_url, headers=start_headers)
            except Exception as e:
                return 'Error while starting upload: ' + repr(e)

            if doUpdate.status_code != 200:
                return "Start request failed " + str(doUpdate.status_code)

        firmware.seek(0)
        encoder = MultipartEncoder(fields={
            'MD5': md5,
            'firmware': ('firmware', firmware, 'application/octet-stream')}
        )

        bar = tqdm(desc='Upload Progress',
                   total=encoder.len,
                   dynamic_ncols=True,
                   unit='B',
                   unit_scale=True,
                   unit_divisor=1024
                   )

        monitor = MultipartEncoderMonitor(encoder, lambda monitor: bar.update(monitor.bytes_read - bar.n))

        post_headers = {
            'Host': host_ip,
            'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/118.0',
            'Accept': '*/*',
            'Accept-Language': 'de,en-US;q=0.7,en;q=0.3',
            'Accept-Encoding': 'gzip, deflate',
            'Referer': f'{upload_url}/update',
            'Connection': 'keep-alive',
            'Content-Type': monitor.content_type,
            'Content-Length': str(monitor.len),
            'Origin': f'{upload_url}'
        }

        try:
            response = requests.post(f"{upload_url}/ota/upload", data=monitor, headers=post_headers, auth=auth)
        except Exception as e:
            return 'Error while uploading: ' + repr(e)
        
        bar.close()
        time.sleep(0.1)
        
        if response.status_code != 200:
            message = "\nUpload failed.\nServer response: " + response.text
            tqdm.write(message)
        else:
            message = "\nUpload successful.\nServer response: " + response.text
            tqdm.write(message)

            
env.Replace(UPLOADCMD=on_upload)
