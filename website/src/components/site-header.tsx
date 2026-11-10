import Link from "next/link";
import { SparklesIcon, StarIcon } from "lucide-react";

import { Button } from "@/components/ui/button";
import { MobileNav } from "@/components/mobile-nav";
import { Search } from "@/components/search";
import { ThemeToggle } from "@/components/theme-toggle";
import { siteConfig } from "@/lib/site-config";

export function SiteHeader() {
  return (
    <header className="fixed inset-x-0 top-0 z-50 border-b border-border/40 bg-background/70 backdrop-blur-xl">
      <div className="mx-auto flex h-16 max-w-6xl items-center justify-between px-4 lg:px-8">
        <Link href="/" className="flex items-center gap-2 font-semibold">
          <SparklesIcon className="size-5 text-primary" />
          8995R
        </Link>
        <div className="flex items-center gap-2">
          <Search />
          <ThemeToggle />
          <Button variant="outline" size="sm" asChild>
            <a
              href={siteConfig.github}
              rel="noopener"
              target="_blank"
              aria-label="Star on GitHub"
            >
              <StarIcon />
              <span className="hidden sm:inline">Star on GitHub</span>
            </a>
          </Button>
        </div>
      </div>
    </header>
  );
}
