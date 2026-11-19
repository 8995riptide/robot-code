import Link from "next/link";
import { SparklesIcon } from "lucide-react";

import { categorySlug, componentsMeta } from "@/lib/components-meta";
import { siteConfig } from "@/lib/site-config";

// The six categories with the most components, from the catalogue itself.
const topCategories = Object.entries(
  componentsMeta.reduce<Record<string, number>>((acc, c) => {
    acc[c.category] = (acc[c.category] ?? 0) + 1;
    return acc;
  }, {}),
)
  .sort((a, b) => b[1] - a[1])
  .slice(0, 6)
  .map(([category]) => category);

const groups = [
  {
    title: "Website",
    links: [
      { text: "Stats", href: "/#stats" },
      { text: "Events", href: "/#events" },
      { text: "Notebook", href: "/#notes" },
      { text: "CAD", href: "/#cad" },
      { text: "Install", href: "/#repo" },
    ],
  },
  {
    title: "Stats from other Websites",
    links: [
      { text: "Robot Statistics", href: "https://robotstatistics.com/teams/8995R" },
      { text: "RoboWorld", href: "https://roboworld.ai/teams/v5rc/8995R" },
      { text: "Showcase", href: "/showcase" },
      { text: "Blog", href: "/blog" },
    ],
  },
  {
    title: "Other Sources",
    links: [
      { text: "llms.txt", href: "/llms.txt" },
      { text: "GitHub", href: siteConfig.github },
      { text: "Velora UI", href: "https://velora.colorlib.com/" },
      { text: "Vercel", href: "https://vercel.com" },
      { text: "Next.js", href: "https://nextjs.org" },
      { text: "Tailwind CSS", href: "https://tailwindcss.com" },
      { text: "Colorlib", href: "https://colorlib.com" },
    ],
  },
];

const headingId = (title: string) =>
  `footer-${title.toLowerCase().replace(/[^a-z]+/g, "-")}`;

export function SiteFooter() {
  return (
    <footer className="border-t border-border/40 py-14">
      <div className="mx-auto grid max-w-7xl grid-cols-2 gap-x-8 gap-y-10 px-4 md:grid-cols-3 lg:grid-cols-[1.4fr_repeat(5,1fr)] lg:px-8">
        <div className="col-span-2 md:col-span-3 lg:col-span-1">
          <Link href="/" className="flex items-center gap-2 font-semibold">
            <SparklesIcon className="size-5 text-primary" />
            8995Riptide
          </Link>
          <p className="mt-3 max-w-xs text-sm text-muted-foreground">
            Everything to do with 8995Riptide
          </p>
          <p className="mt-4 text-xs text-muted-foreground">
            Built with Next.js 16, Tailwind CSS 4, Velora UI, &amp; Motion
          </p>
        </div>
        {groups.map((group) => (
          <nav key={group.title} aria-labelledby={headingId(group.title)}>
            <h2 id={headingId(group.title)} className="text-sm font-semibold">
              {group.title}
            </h2>
            <ul className="mt-4 space-y-2.5 text-sm text-muted-foreground">
              {group.links.map((link) => (
                <li key={link.text}>
                  {/* External URLs and files (llms.txt) aren't Next routes. */}
                  {/^https?:|\.\w+$/.test(link.href) ? (
                    <a
                      href={link.href}
                      rel="noopener"
                      className="transition-colors hover:text-foreground"
                    >
                      {link.text}
                    </a>
                  ) : (
                    <Link
                      href={link.href}
                      // The 404 demo intentionally points at a missing route.
                      prefetch={link.href === "/404-demo" ? false : undefined}
                      className="transition-colors hover:text-foreground"
                    >
                      {link.text}
                    </Link>
                  )}
                </li>
              ))}
            </ul>
          </nav>
        ))}
      </div>
      <div className="mx-auto mt-12 flex max-w-7xl flex-col items-center justify-between gap-2 border-t border-border/40 px-4 pt-6 text-center text-xs text-muted-foreground md:flex-row md:text-left lg:px-8">
        <span>
          © {new Date().getFullYear()} 8995Riptide. All rights reserved.
        </span>
        <span>
          Made by{" "}
          <a
            href="https://colorlib.com"
            rel="noopener"
            className="font-medium text-foreground/80 transition-colors hover:text-foreground"
          >
            Colorlib
          </a>
        </span>
      </div>
    </footer>
  );
}
