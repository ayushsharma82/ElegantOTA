import { useConfig, useTheme } from 'nextra-theme-docs';
import { useRouter } from 'next/router'

const Logo = () => {
  const { resolvedTheme } = useTheme();
  if (resolvedTheme === 'dark') {
    return <img width={160} src="/logo-dark.svg" />
  } else {
    return <img width={160} src="/logo-light.svg" />
  }
}

const config = {
  darkMode: true,
  head() {
    const { asPath, defaultLocale, locale } = useRouter();
    const { frontMatter } = useConfig();
    
    const url = 'https://docs.elegantota.pro' + (defaultLocale === locale ? asPath : `/${locale}${asPath}`)

    return (
      <>
        <title>{frontMatter.title + ' - '}ElegantOTA Docs</title>
        <meta property="og:url" content={url} />
        <meta property="og:title" content={frontMatter.title + ' - ' + 'ElegantOTA Docs'} />
        <meta
          property="og:description"
          content={frontMatter.description || 'ElegantOTA provides a beautiful user interface to upload over-the-air firmware/filesystem updates to your hardware with precise status and progress.'}
        />
      </>
    )
  },
  logo: Logo,
  docsRepositoryBase: 'https://github.com/ayushsharma82/ElegantOTA/tree/docs',
  project: {
    link: 'https://github.com/ayushsharma82/ElegantOTA'
  },
  navbar: {
    extraContent: (
      <a href="https://elegantota.pro" target='_blank' className="text-zinc-900 bg-white hover:bg-zinc-100 border border-zinc-200 focus:ring-4 focus:outline-none focus:ring-zinc-100 font-medium rounded-lg text-sm px-5 py-2 text-center inline-flex items-center dark:focus:ring-zinc-600 dark:bg-zinc-800 dark:border-zinc-700 dark:text-white dark:hover:bg-zinc-700">
        Upgrade to
        <img src="/pro-badge.gif" alt="" width={32} className='me-1 ms-1' />
        <svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2" strokeLinecap="round" strokeLinejoin="round" className="ms-1"><path d="M5 12h14" /><path d="m12 5 7 7-7 7" /></svg>
      </a>
    ),
  },
  footer: {
    component:  (
      <div className="flex flex-col items-center text-xs py-4 px-4 text-zinc-500">
        <div>Copyright © { new Date().getFullYear() } <a href="https://softt.io" target="_blank">Softt</a>. All rights reserved.</div>
      </div>
    )
  },
  // ... other theme options
}

export default config