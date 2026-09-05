/**
 * An image that follows the site's theme.
 *
 * Both sources are rendered and one is hidden in CSS, rather than choosing in
 * JavaScript. That way the right asset is correct in the very first paint —
 * picking inside an effect (as components/Logo.jsx does) briefly shows the
 * light image to dark-mode readers while React hydrates, which nobody notices
 * on a small logo and everybody notices on a full-width banner.
 *
 * Keyed off Tailwind's `dark:` class variant, so it follows the site's own
 * theme toggle rather than the reader's operating system.
 */
export default function ThemeImage({ light, dark, alt = '', className = '', ...props }) {
  return (
    <>
      {/* eslint-disable-next-line @next/next/no-img-element */}
      <img src={light} alt={alt} className={`dark:hidden ${className}`} {...props} />
      {/* eslint-disable-next-line @next/next/no-img-element */}
      <img src={dark} alt={alt} className={`hidden dark:block ${className}`} {...props} />
    </>
  );
}
