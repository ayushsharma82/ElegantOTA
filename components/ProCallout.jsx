import { Callout } from 'nextra/components'

export default function ProCallout() {
  return (
    <a href="https://elegantota.pro" target="_blank">
      <Callout type="info" emoji={<img src="/pro-badge.gif" className='block' alt="" width={48} />}>
        <div className='flex flex-row items-center gap-2'>
          <span>
            This feature is only available in ElegantOTA Pro
          </span>
          <span className='block mb-1'>
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="lucide lucide-external-link"><path d="M15 3h6v6"/><path d="M10 14 21 3"/><path d="M18 13v6a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2V8a2 2 0 0 1 2-2h6"/></svg>
          </span>
        </div>
      </Callout>
    </a>
  )
}