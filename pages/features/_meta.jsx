import Badge from "@/components/Badge";

const metadata = {
  "auto-reboot": {
    title: "Auto Reboot"
  },
  callbacks: {
    title: "Callbacks"
  },
  "hardware-id": {
    title: <span className="flex items-center justify-center gap-2">Hardware ID <Badge /></span>,
  },
  "firmware-version": {
    title: <span className="flex items-center justify-center gap-2">Firmware Version <Badge /></span>,
  },
  "custom-title": {
    title: <span className="flex items-center justify-center gap-2">Custom Title <Badge /></span>,
  }
}

export default metadata