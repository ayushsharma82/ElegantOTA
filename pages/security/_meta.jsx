import Badge from "@/components/Badge";

const metadata = {
  authentication: "Authentication",
  "disable-firmware-ota": {
    title: <span className="flex items-center justify-center gap-2">Disable Firmware OTA <Badge /></span>,
  },
  "disable-filesystem-ota": {
    title: <span className="flex items-center justify-center gap-2">Disable Filesystem OTA <Badge /></span>,
  },
  "disable-direct-download": {
    title: <span className="flex items-center justify-center gap-2">Disable Direct Download <Badge /></span>,
  }
};

export default metadata;
