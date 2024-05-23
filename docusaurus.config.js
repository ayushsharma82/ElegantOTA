// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion

const lightCodeTheme = require('prism-react-renderer/themes/github');
const darkCodeTheme = require('prism-react-renderer/themes/dracula');

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: 'ElegantOTA Docs',
  tagline: 'OTA update library for ESP8266 & ESP32 microcontrollers',
  url: 'https://docs.elegantota.pro',
  baseUrl: '/',
  onBrokenLinks: 'warn',
  onBrokenMarkdownLinks: 'warn',
  // favicon: 'img/dash-mini-logo.ico',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: 'ayushsharma82', // Usually your GitHub org/user name.
  projectName: 'ElegantOTA', // Usually your repo name.
  deploymentBranch: 'gh-pages',
  trailingSlash: true,

  // Even if you don't use internalization, you can use this field to set useful
  // metadata like html lang. For example, if your site is Chinese, you may want
  // to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        gtag: {
          trackingID: 'G-H1X62VMQNV',
          anonymizeIP: true,
        },
        docs: {
          disableVersioning: true,
          routeBasePath: '/',
          sidebarPath: require.resolve('./sidebars.js'),
        },
        blog: false,
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
        sitemap: {
          changefreq: 'weekly',
          priority: 0.5,
          ignorePatterns: ['/tags/**'],
          filename: 'sitemap.xml',
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      colorMode: {
        defaultMode: 'dark',
        respectPrefersColorScheme: false,
      },
      navbar: {
        title: "",
        logo: {
          src: 'v3/img/feature-mini.png',
          alt: 'ElegantOTA',
          width: 180
        },
        items: [
          // {
          //   type: 'doc',
          //   docId: 'intro',
          //   position: 'left',
          //   label: 'Docs',
          // },
          // {to: '/blog', label: 'Blog', position: 'left'},
          {
            href: "https://github.com/ayushsharma82/ElegantOTA/",
            position: "right",
            className: "header-github-link",
            "aria-label": "GitHub repository",
          },
        ],
      },
      footer: {
        style: 'light',
        links: [
          {
            title: 'Docs',
            items: [
              {
                label: 'Getting Started',
                to: '/getting-started',
              },
              {
                label: 'Examples',
                to: '/examples',
              },
              {
                label: 'Commercial License',
                to: '/commercial-license',
              },
            ],
          },
          {
            title: 'Community',
            items: [
              {
                label: 'Github',
                href: 'https://github.com/ayushsharma82/ElegantOTA/',
              },
              {
                label: 'Twitter',
                href: 'https://twitter.com/asrocks5',
              },
            ],
          },
          {
            title: 'Support',
            items: [
              {
                label: 'Create an Issue (Repo)',
                href: 'https://github.com/ayushsharma82/ElegantOTA/issues',
              },
              {
                label: 'Contact me',
                href: 'https://elegantota.pro/support',
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} SOFTT. All rights reserved.`,
      },
      prism: {
        theme: lightCodeTheme,
        darkTheme: darkCodeTheme,
      },
    }),
};

module.exports = config;
