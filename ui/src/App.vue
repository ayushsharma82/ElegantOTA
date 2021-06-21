<template>
  <!-- eslint-disable max-len -->
  <main class="container">
    <div class="columns mt-3">
      <div class="col-12 mt-3 text-center">
        <img width="280px" alt="ElegantOTA" src="data:image/svg+xml;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0idXRmLTgiPz4KPHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB2ZXJzaW9uPSIxLjEiIGlkPSJMYXllcl8xIiB4PSIwcHgiIHk9IjBweCIgdmlld0JveD0iMCAwIDI1NCA4MyIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgMjU0IDgzOyI+CjxzdHlsZSB0eXBlPSJ0ZXh0L2NzcyI+Cgkuc3Qwe2ZpbGw6IzJFMzAzNDt9Cgkuc3Qxe2ZpbGw6IzQ4OEVGRjt9Cjwvc3R5bGU+CjxnIGlkPSJfeDMwX2I3NDI0NjctMjdlYS1hZTNmLTdjZmEtY2EwZTEwYWMwNGU3IiB0cmFuc2Zvcm09Im1hdHJpeCgyLjIsMCwwLDIuMiwxMDMuODg3NjQxNjY4MzE5NywxMzIuMzU1OTk2MDM2NTI5NTUpIj4KCTxwYXRoIGNsYXNzPSJzdDAiIGQ9Ik0tNi4xLTQ1LjR2LTFILTEzdjkuM2g2Ljh2LTFoLTUuOHYtMy4xaDUuMnYtMWgtNS4ydi0zLjFILTYuMXogTS0zLjYtNDdoLTEuMXY5LjhoMS4xVi00N3ogTTEuMy0zOCAgIGMtMS40LDAtMi4zLTEtMi41LTIuMmg1Ljl2LTAuNGMwLTItMS4zLTMuNi0zLjUtMy42cy0zLjUsMS42LTMuNSwzLjZTLTAuOC0zNywxLjMtMzdDMy0zNyw0LTM3LjksNC41LTM5LjJIMy4zICAgQzMtMzguNSwyLjMtMzgsMS4zLTM4eiBNMS4yLTQzLjNjMS4zLDAsMi4yLDAuOSwyLjQsMi4xaC00LjhDLTAuOS00Mi40LTAuMS00My4zLDEuMi00My4zeiBNMTEuNS00NC4ydjEuMSAgIGMtMC41LTAuOC0xLjMtMS4yLTIuNS0xLjJjLTIsMC0zLjQsMS42LTMuNCwzLjZjMCwyLDEuMywzLjYsMy40LDMuNmMxLjIsMCwyLTAuNSwyLjUtMS4zdjFjMCwxLjQtMC43LDIuMi0yLjMsMi4yICAgYy0xLjEsMC0xLjgtMC40LTItMS4xSDUuOWMwLjQsMS4yLDEuNSwyLDMuMywyYzIuMSwwLDMuMy0xLjEsMy4zLTMuMXYtNi44SDExLjV6IE05LjEtMzguMWMtMS42LDAtMi41LTEuMi0yLjUtMi42ICAgYzAtMS40LDAuOS0yLjYsMi41LTIuNmMxLjUsMCwyLjQsMS4yLDIuNCwyLjZDMTEuNS0zOS4zLDEwLjYtMzguMSw5LjEtMzguMXogTTE3LjMtNDQuM2MtMiwwLTMuNCwxLjYtMy40LDMuNnMxLjMsMy42LDMuNCwzLjYgICBjMS4yLDAsMi0wLjUsMi41LTEuMnYxLjFoMXYtN2gtMXYxLjFDMTkuMy00My44LDE4LjQtNDQuMywxNy4zLTQ0LjN6IE0xNy40LTM4Yy0xLjYsMC0yLjUtMS4yLTIuNS0yLjdjMC0xLjQsMC45LTIuNywyLjUtMi43ICAgYzEuNiwwLDIuNCwxLjIsMi40LDIuN0MxOS44LTM5LjIsMTktMzgsMTcuNC0zOHogTTIyLjctNDQuMnY3aDF2LTRjMC0xLjMsMS0yLjEsMi4xLTIuMWMxLjIsMCwyLDAuOCwyLDIuMXY0aDF2LTQuMSAgIGMwLTItMS4zLTMtMi44LTNjLTEuMSwwLTEuOCwwLjUtMi4zLDEuMnYtMS4xSDIyLjd6IE0zMi4yLTM3LjJ2LTYuMWgxLjZ2LTAuOWgtMS42di0yLjVoLTEuMXYyLjVoLTEuNHYwLjloMS40djYuMUgzMi4yeiAgICBNMzkuMy00Ni41Yy0yLjgsMC00LjcsMi4xLTQuNyw0LjhjMCwyLjYsMS45LDQuNyw0LjcsNC43czQuNy0yLjEsNC43LTQuN0M0NC00NC40LDQyLjEtNDYuNSwzOS4zLTQ2LjV6IE0zOS4zLTM4LjEgICBjLTIuMywwLTMuNy0xLjYtMy43LTMuN2MwLTIuMSwxLjQtMy43LDMuNy0zLjdzMy43LDEuNiwzLjcsMy43QzQzLTM5LjcsNDEuNi0zOC4xLDM5LjMtMzguMXogTTUxLjktNDYuNGgtNy41djFoMy4ydjguM2gxdi04LjMgICBoMy4yVi00Ni40eiBNNTYuNS00Ni40aC0xLjNsLTMuOSw5LjNoMS4ybDEuMS0yLjdoNC42bDEuMSwyLjdoMS4yTDU2LjUtNDYuNHogTTU0LTQwLjhsMS45LTQuNWwxLjksNC41SDU0eiIvPgo8L2c+CjxnIGlkPSJkYzY4OGQxZi1hMDY2LWI3ZTctOGFiYy0xMTVmYTQwZTk0NDUiIHRyYW5zZm9ybT0ibWF0cml4KDAuMjI1NTIwNTc0ODgyOTcxMTEsMCwwLDAuMjI1NTIwNTc0ODgyOTcxMTEsMzQuNTIyNzQzOTgxNjY2ODU2LDExNy4wMTc3NDQ5NjcyNzM1KSI+Cgk8cGF0aCBjbGFzcz0ic3QxIiBkPSJNMTE5LTM0Ny42YzUuNywwLDcuOCw2LjYsNC41LDEwLjhjLTcuMiw4LjQtMTQuNCwxNi41LTIxLjYsMjQuOWMtMi4xLDIuNC02LjYsMi40LTksMCAgIGMtNy4yLTguNC0xNC40LTE2LjUtMjEuNi0yNC45Yy00LjUtNS4xLDEuMi0xMi4zLDYuMy0xMC44aDEzLjJjLTcuMi0yOC44LTI5LjEtNTIuNS01OC44LTU5LjFjLTUuNy0xLjItMTEuNC0xLjgtMTcuMS0xLjggICBjLTI4LjgsMC01NS41LDE1LjktNjkuNiw0MmMtMy45LDcuMi0xNC43LDAuOS0xMC44LTYuM2MxOS4yLTM0LjgsNTkuNC01NC45LDk4LjctNDYuMmMzNS40LDcuNSw2MywzNiw3MC4yLDcxLjQgICBDMTAzLjQtMzQ3LjYsMTE5LTM0Ny42LDExOS0zNDcuNnogTS04My4yLTMwOS4yYy01LjcsMC03LjgtNi42LTQuNS0xMC44YzcuMi04LjQsMTQuNC0xNi41LDIxLjYtMjQuOWMyLjEtMi40LDYuNi0yLjQsOSwwICAgYzcuMiw4LjQsMTQuNCwxNi41LDIxLjYsMjQuOWM0LjUsNS4xLTEuMiwxMi4zLTYuMywxMC44SC01NWM3LjIsMjguOCwyOS4xLDUyLjUsNTguOCw1OS4xYzUuNywxLjIsMTEuNCwxLjgsMTcuMSwxLjggICBjMjguOCwwLDU1LjUtMTUuOSw2OS42LTQyYzMuOS03LjIsMTQuNy0wLjksMTAuOCw2LjNjLTE5LjIsMzUuMS01OS40LDU1LjItOTguNyw0Ni41Yy0zNS40LTcuOC02My4zLTM2LjMtNzAuNS03MS43SC04My4yeiIvPgo8L2c+Cjwvc3ZnPgo=">
      </div>
      <div class="col-12 p-centered"></div>
      <div class="col-12 mt-3 p-centered" v-if="loading">
        <div class="col-3 col-sm-10 p-centered">
          <div class="loading loading-lg mt-3"></div>
        </div>
      </div>
      <transition name="fade" mode="out-in">
        <div class="col-12 mt-3 pt-2 p-centered" v-if="!loading && !uploading && OTAError !== null" key="error">
          <div class="col-3 col-sm-9 col-md-6 p-centered text-center">
            <svg width="32px" height="32px" style="vertical-align: middle;" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
              <g stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <circle id="Oval-5" fill="#DF4759" opacity="0.3" cx="12" cy="12" r="10"></circle>
                <rect id="Rectangle-9" fill="#DF4759" x="11" y="7" width="2" height="8" rx="1"></rect>
                <rect id="Rectangle-9-Copy" fill="#DF4759" x="11" y="16" width="2" height="2" rx="1"></rect>
              </g>
            </svg>
            <span style="vertical-align: middle;" class="ml-2"> {{ OTAError }} </span>
            <br>
            <br>
            <div class="mt-3">
              <button class="btn btn-light mr-2" @click="clear">
                <svg xmlns="http://www.w3.org/2000/svg" class="pt-1" width="16px" height="16px" viewBox="0 0 24 24">
                  <g data-name="Layer 2">
                    <g data-name="arrow-back">
                      <rect width="24" height="24" transform="rotate(90 12 12)" opacity="0" />
                      <path
                        fill="currentColor"
                        d="M19 11H7.14l3.63-4.36a1 1 0 1 0-1.54-1.28l-5 6a1.19 1.19 0 0 0-.09.15c0 .05 0 .08-.07.13A1 1 0 0 0 4 12a1 1 0 0 0 .07.36c0 .05 0 .08.07.13a1.19 1.19 0 0 0 .09.15l5 6A1 1 0 0 0 10 19a1 1 0 0 0 .64-.23 1 1 0 0 0 .13-1.41L7.14 13H19a1 1 0 0 0 0-2z" />
                    </g>
                  </g>
                </svg>
                Back
              </button>
              <button class="btn btn-primary ml-2" @click="retryOTA">
                <svg xmlns="http://www.w3.org/2000/svg" class="pt-1" width="16px" height="16px" viewBox="0 0 24 24">
                  <g data-name="Layer 2">
                    <g data-name="refresh">
                      <rect width="24" height="24" opacity="0" />
                      <path
                        fill="currentColor"
                        d="M20.3 13.43a1 1 0 0 0-1.25.65A7.14 7.14 0 0 1 12.18 19 7.1 7.1 0 0 1 5 12a7.1 7.1 0 0 1 7.18-7 7.26 7.26 0 0 1 4.65 1.67l-2.17-.36a1 1 0 0 0-1.15.83 1 1 0 0 0 .83 1.15l4.24.7h.17a1 1 0 0 0 .34-.06.33.33 0 0 0 .1-.06.78.78 0 0 0 .2-.11l.09-.11c0-.05.09-.09.13-.15s0-.1.05-.14a1.34 1.34 0 0 0 .07-.18l.75-4a1 1 0 0 0-2-.38l-.27 1.45A9.21 9.21 0 0 0 12.18 3 9.1 9.1 0 0 0 3 12a9.1 9.1 0 0 0 9.18 9A9.12 9.12 0 0 0 21 14.68a1 1 0 0 0-.7-1.25z" />
                    </g>
                  </g>
                </svg>
                Retry
              </button>
            </div>
          </div>
        </div>
        <div class="col-12 mt-3 pt-2 p-centered" v-else-if="!loading && !uploading && OTASuccess" key="success">
          <div class="col-3 col-sm-9 col-md-6 p-centered text-center">
            <svg width="32px" height="32px" style="vertical-align: middle;" viewBox="0 0 24 24" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
              <g stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                <rect id="bound" x="0" y="0" width="24" height="24"></rect>
                <circle id="Oval-5" fill="#42BA96" opacity="0.3" cx="12" cy="12" r="10"></circle>
                <path d="M16.7689447,7.81768175 C17.1457787,7.41393107 17.7785676,7.39211077 18.1823183,7.76894473 C18.5860689,8.1457787 18.6078892,8.77856757 18.2310553,9.18231825 L11.2310553,16.6823183 C10.8654446,17.0740439 10.2560456,17.107974 9.84920863,16.7592566 L6.34920863,13.7592566 C5.92988278,13.3998345 5.88132125,12.7685345 6.2407434,12.3492086 C6.60016555,11.9298828 7.23146553,11.8813212 7.65079137,12.2407434 L10.4229928,14.616916 L16.7689447,7.81768175 Z" id="Path-92" fill="#42BA96"></path>
              </g>
            </svg>
            <span style="vertical-align: middle;" class="ml-2 mb-2"> OTA Success </span>
            <br>
            <br>
            <button class="btn btn-primary mt-3" @click="clear">
              <svg xmlns="http://www.w3.org/2000/svg" class="pt-1" width="16px" height="16px" viewBox="0 0 24 24">
                <g data-name="Layer 2">
                  <g data-name="arrow-back">
                    <rect width="24" height="24" transform="rotate(90 12 12)" opacity="0" />
                    <path
                      fill="currentColor"
                      d="M19 11H7.14l3.63-4.36a1 1 0 1 0-1.54-1.28l-5 6a1.19 1.19 0 0 0-.09.15c0 .05 0 .08-.07.13A1 1 0 0 0 4 12a1 1 0 0 0 .07.36c0 .05 0 .08.07.13a1.19 1.19 0 0 0 .09.15l5 6A1 1 0 0 0 10 19a1 1 0 0 0 .64-.23 1 1 0 0 0 .13-1.41L7.14 13H19a1 1 0 0 0 0-2z" />
                  </g>
                </g>
              </svg>
              Back
            </button>
          </div>
        </div>
        <div class="col-12 mt-3 p-centered" v-else-if="!loading && !uploading" key="otainput">
          <div class="col-3 col-sm-9 col-md-6 p-centered">
            <div class="form-group pt-2 mt-2">
              <label class="form-radio form-inline mr-2">
                <input type="radio" name="firmwaretype" for="firmwaretype" value="firmware" v-model="type"><i class="form-icon"></i> Firmware
              </label>
              <label class="form-radio form-inline ml-2">
                <input type="radio" name="firmwaretype" for="firmwaretype" value="filesystem" v-model="type"><i class="form-icon"></i> Filesystem
              </label>
            </div>
            <div class="form-group pt-2 mt-3">
              <input class="form-input file-input" type="file" ref="file" accept=".bin,.bin.gz" @change="uploadOTA">
            </div>
          </div>
        </div>
      </transition>
      <transition name="fade" mode="out-in">
        <div class="col-12 mt-3 mb-2 pt-2 p-centered" v-if="!loading && uploading">
          <div class="col-2 mt-3 mb-2 col-sm-7 col-md-4 text-right p-centered">
            <div class="bar mt-3 bar-sm">
              <div class="bar-item tooltip" :data-tooltip="progress+'%'" :style="{ width: progress+'%' }"></div>
            </div>
            <div class="pt-2">{{progress}}%</div>
          </div>
        </div>
      </transition>
      <div class="col-12 mt-3 p-centered"></div>
    </div>
    <transition name="fade" mode="out-in">
      <div class="columns mt-3" v-if="!loading">
        <div class="col-12 text-center">
          <span class="label label-rounded mr-2">{{ deviceData.id }}</span> - <span class="label label-rounded label-primary ml-2">{{ deviceData.hardware }}</span>
        </div>
      </div>
    </transition>
  </main>
</template>

<script>
export default {
  name: 'App',

  data() {
    return {
      loading: true,
      uploading: false,
      progress: 0,
      OTAError: null,
      OTASuccess: false,

      type: 'firmware',
      file: null,
      deviceData: {
        id: null,
        hardware: null,
      },
    };
  },

  methods: {
    fileMD5(file) {
      return new Promise((resolve, reject) => {
        const blobSlice = File.prototype.slice
          || File.prototype.mozSlice || File.prototype.webkitSlice;
        const chunkSize = 2097152; // Read in chunks of 2MB
        const chunks = Math.ceil(file.size / chunkSize);
        const spark = new this.SparkMD5.ArrayBuffer();
        const fileReader = new FileReader();
        let currentChunk = 0;
        let loadNext;

        fileReader.onload = (e) => {
          spark.append(e.target.result); // Append array buffer
          currentChunk += 1;

          if (currentChunk < chunks) {
            loadNext();
          } else {
            const md5 = spark.end();
            resolve(md5);
          }
        };

        fileReader.onerror = (e) => {
          reject(e);
        };

        loadNext = () => {
          const start = currentChunk * chunkSize;
          const end = ((start + chunkSize) >= file.size) ? file.size : start + chunkSize;

          fileReader.readAsArrayBuffer(blobSlice.call(file, start, end));
        };

        loadNext();
      });
    },
    uploadOTA(event) {
      this.uploading = true;
      const formData = new FormData();
      if (event !== null) {
        [this.file] = event.target.files;
      }
      const request = new XMLHttpRequest();

      request.addEventListener('load', () => {
        // request.response will hold the response from the server
        if (request.status === 200) {
          this.OTASuccess = true;
        } else if (request.status !== 500) {
          this.OTAError = `[HTTP ERROR] ${request.statusText}`;
        } else {
          this.OTAError = request.responseText;
        }
        this.uploading = false;
        this.progress = 0;
      });

      // Upload progress
      request.upload.addEventListener('progress', (e) => {
        this.progress = Math.trunc((e.loaded / e.total) * 100);
      });

      request.withCredentials = true;

      this.fileMD5(this.file)
        .then((md5) => {
          formData.append('MD5', md5);
          formData.append(this.type, this.file, this.type);
          request.open('post', '/update');
          request.send(formData);
        })
        .catch(() => {
          this.OTAError = 'Unknown error while upload, check the console for details.';
          this.uploading = false;
          this.progress = 0;
        });
    },

    retryOTA() {
      this.OTAError = null;
      this.OTASuccess = false;
      this.uploadOTA(null);
    },

    clear() {
      this.OTAError = null;
      this.OTASuccess = false;
    },
  },

  mounted() {
    if (process.env.NODE_ENV === 'production') {
      fetch('/update/identity').then(async (response) => {
        if (response.ok) {
          this.deviceData = await response.json();
          this.loading = false;
        }
      });
    }
  },

};
</script>

<style lang="scss">
$primary-color: #488EFF;
// Variables and mixins
@import "~spectre.css/src/variables";
@import "~spectre.css/src/mixins";

/*! Spectre.css v#{$version} | MIT License | github.com/picturepan2/spectre */
// Reset and dependencies
@import "~spectre.css/src/normalize";
@import "~spectre.css/src/base";

// Elements
@import "~spectre.css/src/typography";

@import "~spectre.css/src/labels";
@import "~spectre.css/src/buttons";
@import "~spectre.css/src/tooltips";
@import "~spectre.css/src/cards";
@import "~spectre.css/src/bars";
@import "~spectre.css/src/forms";

@import "~spectre.css/src/layout";

@import "~spectre.css/src/animations";
@import "~spectre.css/src/utilities";

.logo{
  width: 100%;
  max-width: 320px;
}

.card{
  border: 0;
  box-shadow: 0 0.25rem 1rem rgba(48,55,66,.1);
  border-radius: 0.275rem;
}

.label{
  font-size: 0.65rem !important;
}

.file-input{
  border-radius: 0.275rem;
}

.pt-3{
  padding-top: 32px;
}

.mt-3{
  margin-top: 24px;
}

.fade-enter-active, .fade-leave-active {
  transition: opacity .25s;
}
.fade-enter, .fade-leave-to /* .fade-leave-active below version 2.1.8 */ {
  opacity: 0;
}
</style>
