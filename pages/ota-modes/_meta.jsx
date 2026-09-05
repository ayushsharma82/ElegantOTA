import Badge from "@/components/Badge";

const metadata = {
  file: {
    title: "File"
  },
  "direct-download": {
    title: <span className="flex items-center justify-center gap-2">Direct Download <Badge /></span>,
  },
  auto: {
    title: <span className="flex items-center justify-center gap-2">Auto Update <Badge /></span>,
  }
};

export default metadata;
