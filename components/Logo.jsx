'use client'

import { useEffect, useState } from 'react';
import { useTheme } from 'next-themes'

export const Logo = () => {
  const [isDark, setIsDark] = useState(false);
  const { resolvedTheme } = useTheme();

  useEffect(() => {
    setIsDark(resolvedTheme === 'dark');
  }, [resolvedTheme]);

  return (
    // eslint-disable-next-line @next/next/no-img-element
    <img width={160} src={isDark ? "/logo-dark.svg" : "/logo-light.svg"} alt="ElegantOTA" />
  );
}