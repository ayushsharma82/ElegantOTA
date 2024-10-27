import Badge from "@/components/Badge";

const metadata = {
  "index": {
    title: "Introduction"
  },
  "getting-started": {
    "title": "Getting Started",
    open: true
  },
  security: {
    title: "Security",
    open: true
  },
  "features": {
    "title": "Features",
    head: {
      titleTemplate: '%s - Features'
    },
    open: true
  },
  "branding": {
    title: <span className="flex items-center justify-center gap-2">Branding <Badge /></span>,
  },
  "commercial-license": {
    title: "Commercial License"
  }
}

export default metadata