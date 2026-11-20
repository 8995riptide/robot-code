import type { Metadata } from "next";
import Link from "next/link";
import { HyperText } from "@/components/velora/hyper-text";
import ModelViewer from '../components/ModelViewer';
import InteractiveTerminal from "../components/ui/terminal";
import {
  AccessibilityIcon,
  AppWindowIcon,
  ArrowRightIcon,
  BoxIcon,
  ChevronsDownIcon,
  FeatherIcon,
  GalleryHorizontalIcon,
  GaugeIcon,
  GitCompareIcon,
  GlobeIcon,
  LayersIcon,
  LayoutGridIcon,
  LoaderIcon,
  MenuIcon,
  MessageSquareQuoteIcon,
  MonitorSmartphoneIcon,
  MousePointer2Icon,
  MousePointerClickIcon,
  PaletteIcon,
  SparklesIcon,
  TerminalIcon,
  TextCursorInputIcon,
  TypeIcon,
  WavesIcon,
  ZapIcon,
} from "lucide-react";

import {
  Accordion,
  AccordionContent,
  AccordionItem,
  AccordionTrigger,
} from "@/components/ui/accordion";
import { BlockThumbnail } from "@/components/docs/block-thumbnail";
import { CopyButton } from "@/components/docs/copy-button";
import { LiveDemo } from "@/components/home/live-demo";
import { SiteFooter } from "@/components/site-footer";
import { SiteHeader } from "@/components/site-header";
import { StackLogo, stackNames } from "@/components/template/stack-logos";
import { AuroraBackground } from "@/components/velora/aurora-background";
import { GridPattern } from "@/components/velora/grid-pattern";
import {
  BarsLoader,
  DotsLoader,
  OrbitLoader,
  PulseLoader,
  SpinnerLoader,
} from "@/components/velora/loaders";
import { AnimatedTooltip } from "@/components/velora/animated-tooltip";

import { Marquee } from "@/components/velora/marquee";
import { OrbitingCircles } from "@/components/velora/orbiting-circles";
import { blocksMeta, freeBlocks, proBlocks } from "@/lib/blocks-meta";
import componentStats from "@/lib/component-stats.json";
import {
  events,
  categorySlug,
  componentsMeta,
} from "@/lib/components-meta";
import { JsonLd, publisher } from "@/lib/seo";
import { siteConfig } from "@/lib/site-config";
import { cn } from "@/lib/utils";
import { AnimatedList } from "@/components/velora/animated-list";
import MarkdownDisplay from "@/components/blocks/markdown-display";
import { NumberTicker } from "@/components/velora/number-ticker";
import { AnimatedGradientText } from "@/components/velora/animated-gradient-text";
import { Typewriter } from "@/components/velora/typewriter";
import { ShimmerButton } from "@/components/velora/shimmer-button";
import { MovingBorder } from "@/components/velora/moving-border";
import { ScrollProgress } from "@/components/velora/scroll-progress";
import { FollowingPointer } from "@/components/velora/following-pointer";
import { Lens } from "@/components/velora/lens";
import { TiltCard } from "@/components/velora/tilt-card";
import { TerminalView } from "@/components/velora/terminal";
import { Timeline } from "@/components/velora/timeline";
export const metadata: Metadata = {
  alternates: { canonical: "/" },
};

const stats = componentStats as Record<
  string,
  { bytes: number; gzip: number; deps: string[] }
>;
const statList = Object.values(stats);
const zeroDeps = statList.filter((s) => s.deps.length === 0).length;
const underThreeKb = statList.filter((s) => s.gzip <= 3 * 1024).length;
const kb = (slug: string) => (stats[slug].gzip / 1024).toFixed(1);

// A sample of names for the marquee tile; the full list would bloat the HTML.
const marqueeSample = componentsMeta.filter((_, i) => i % 3 === 0);
const marqueeRows = [
  marqueeSample.slice(0, Math.ceil(marqueeSample.length / 2)),
  marqueeSample.slice(Math.ceil(marqueeSample.length / 2)),
];

const REGISTRY = `${siteConfig.url}/r/{name}.json`;
const installSteps = [
  {
    title: "1. Clone the repo",
    command: `git clone ${siteConfig.github}`,
  },
  {
    title: "2. Explore the repository",
    command: "cd robot-code",
  },
];
const INSTALL = "npx shadcn@latest add @velora/marquee";

const categoryIcons: Record<string, string> = {
  "IPSD V5 Robotics Invitational": "https://events.vex.com/robot-competitions/vex-robotics-competition/VE-V5-26-66342.html#general-info",
};

const featuredBlocks = [
  "hero-globe",
  "features-bento",
  "pricing-three-tiers",
  "testimonials-marquee",
].flatMap((slug) => blocksMeta.filter((b) => b.slug === slug));

const faqs: { q: string; a: React.ReactNode }[] = [
  {
    q: "Is Velora UI free for commercial projects?",
    a: (
      <>
        Yes. Every component, block and the SaaS template are MIT licensed, so you can
        use them in personal, client and commercial work. The source is on{" "}
        <a href={siteConfig.github} className="text-foreground underline underline-offset-4">
          GitHub
        </a>
        .
      </>
    ),
  },
  {
    q: "What do I need to use it?",
    a: "React 19, Tailwind CSS v4 and a shadcn/ui project. About half the components use Motion; the shadcn CLI installs it when a component needs it.",
  },
  {
    q: "Does it work with Radix UI or Base UI?",
    a: "Both. Velora components don't import Radix or Base UI, so they work whichever primitive layer your shadcn project uses.",
  },
  {
    q: "What happens when someone prefers reduced motion?",
    a: "Every animated component respects prefers-reduced-motion on its own, so it still does after you install it. Anything that loops pauses on hover and focus, and each docs page spells out what reduced-motion, keyboard and screen-reader users get.",
  },
  {
    q: "How do installs work?",
    a: (
      <>
        Components are source files you own. The shadcn CLI copies them into{" "}
        <code className="font-mono text-foreground">components/velora</code>, merges any
        keyframes and brand tokens into your CSS and installs npm dependencies. There is no
        Velora package to update. Blocks install the same way and bring the components they
        use along.
      </>
    ),
  },
  {
    q: "Can my AI agent install components?",
    a: (
      <>
        Yes. Velora is a standard shadcn registry, so the shadcn MCP server can search and
        install it by name. <a href="/llms.txt" className="text-foreground underline underline-offset-4">llms.txt</a>{" "}
        lists every component with its size and install command.
      </>
    ),
  },
  {
    q: "What is Velora Pro?",
    a: (
      <>
        {proBlocks.length} application blocks for dashboards and SaaS apps, from $
        {siteConfig.pro.personal.price} paid once{siteConfig.pro.onSale ? "" : ", launching soon"}.
        Everything free today stays free and MIT.{" "}
        <Link href="/pricing" className="text-foreground underline underline-offset-4">
          See pricing
        </Link>
        .
      </>
    ),
  },
];

/** A showcase tile: a live component with its name, docs link and size. */
function Tile({
  slug,
  className,
  children,
}: {
  slug: string;
  className?: string;
  children: React.ReactNode;
}) {
  const meta = componentsMeta.find((c) => c.slug === slug);
  const s = stats[slug];
  return (
    <figure
      className={cn(
        "relative flex min-w-0 flex-col overflow-hidden rounded-2xl border bg-card/50",
        className
      )}
    >
      <div className="relative min-h-0 flex-1 overflow-hidden">{children}</div>
      <figcaption className="flex flex-wrap items-center justify-between gap-x-3 gap-y-0.5 border-t border-border/60 px-4 py-2.5 text-sm">
        <Link
          href={`/components/${slug}`}
          className="group/link inline-flex min-w-0 items-center gap-1 rounded-sm font-medium transition-colors outline-none hover:text-primary focus-visible:ring-2 focus-visible:ring-ring"
        >
          <span className="truncate">{meta?.title ?? slug}</span>
          <ArrowRightIcon className="size-3.5 shrink-0 text-muted-foreground transition-transform group-hover/link:translate-x-0.5" />
        </Link>
        {s && (
          <span className="shrink-0 font-mono text-xs text-muted-foreground">
            {kb(slug)} KB{s.deps.length === 0 && " · 0 deps"}
          </span>
        )}
      </figcaption>
    </figure>
  );
}

function SectionHeading({
  id,
  eyebrow,
  title,
  children,
  className,
}: {
  id: string;
  eyebrow: string;
  title: React.ReactNode;
  children?: React.ReactNode;
  className?: string;
}) {
  return (
    <div className={cn("max-w-2xl", className)}>
      <p className="text-sm font-medium text-primary">{eyebrow}</p>
      <h2
        id={id}
        className="mt-2 text-3xl font-semibold tracking-tight text-balance lg:text-4xl"
      >
        {title}
      </h2>
      {children && <p className="mt-3 text-muted-foreground text-pretty">{children}</p>}
    </div>
  );
}

export default function Home() {
  const why = [
    {
      icon: AccessibilityIcon,
      metric: "60",
      label: "accessibility fixes, documented per component",
      links: [{ href: "/components/animated-tabs#accessibility", label: "See an example" }],
    },
    {
      icon: GaugeIcon,
      metric: "≤ 3 KB",
      label: `${underThreeKb} of ${componentsMeta.length} components, gzipped`,
      links: [{ href: "/components/marquee", label: `Marquee: ${kb("marquee")} KB` }],
    },
    {
      icon: TerminalIcon,
      metric: "1 command",
      label: "code, keyframes, tokens and dependencies",
      links: [{ href: "/components/get-started", label: "How installs work" }],
    },
    {
      icon: GitCompareIcon,
      metric: "3",
      label: "comparisons, measured the same way",
      links: [
        { href: "/compare/aceternity-ui", label: "Aceternity" },
        { href: "/compare/magic-ui", label: "Magic UI" },
        { href: "/compare/react-bits", label: "React Bits" },
      ],
    },
  ];
  const timeline = [
  {
    title: "Week 1",
    content: (
      <>
        <p className="text-muted-foreground">
          The first commit. A few build ideas, a few CAD outlines, a few lines of code. First design ideas, lift ideas, drivetrain and claw/toggle ideas. DR4B or Cascade? One sided or two-sided claw? Gear ratios?
        </p>
      </>
    ),
  },
  {
    title: "Week 2",
    content: (
      <>
        <p className="text-muted-foreground">
          Two sided claw using Vex Claw Kit is planned. CAD finished, temporary DR4B planned. Drivetrain close to being complete. First competition is coming up, so we are focusing on building and programming the robot.
        </p>
      </>
    ),
  },
  {
    title: "Week 3",
    content: (
      <>
        <p className="text-muted-foreground">
          Fixed drivetrain, DR4B and claw. Tested all three. Code written and compiled. One sided claw built(no parts for two sided), regular four bar built(no parts for DR4B).
        </p>
      </>
    ),
  },
  {
    title: "Oct 23rd Competition",
    content: (
      <p className="text-muted-foreground">
        First competition. Did pretty well, placed 6th out of 21. Drivetrain worked fine, as well as lift, toggles and claw. Will make improvements to drivetrain and lift for next competition. Will also make a DR4B/cascade for next competition. 
      </p>
    ),
  },
  {
    title: "Week 4",
    content: (
      <p className="text-muted-foreground">
        DR4B or Cascade? Planned both, decided to build chain cascade first. Optimized code and CAD. Fixed drivetrain with better gear ratio
      </p>
    ),
  },
    {
    title: "Week 5",
    content: (
      <p className="text-muted-foreground">
        Cascade structure bult, but no sprokets or chain available. Perhaps string? Tested code, but no way to test cascade. Drivetrain and CAD optimized.
      </p>
    ),
  },
      {
    title: "Week 6",
    content: (
      <p className="text-muted-foreground">
        No materials for cascade, so building DR4B. DR4B cadded, halfway built. Code and drivetrain optimized and tested. We are not quite ready for the next competition, but we will be ready for the one after that.
      </p>
    ),
  },
        {
    title: "Nov 13th Competition",
    content: (
      <p className="text-muted-foreground">
        Did decent in comp, got 6th. Got carried, DR4B wasn't done, brain and code was giving errors, drivetrain was very slow. Need to build lift and optimize code and drivetrain for next comp.
      </p>
    ),
  },
];
  const FRAME_WIDTH = 1280
  return (
    <>
      <JsonLd
        data={[
          {
            "@type": "WebSite",
            name: "8995 Riptide",
            url: "https://8995riptide.vercel.app",
            description: "The website for all things 8995 Riptide",
            publisher,
          },
          { ...publisher, sameAs: [siteConfig.github] },
        ]}
      />
                  <InteractiveTerminal
        command="pnpm run dev"
        autoExecute
        variant="sky"
        title="bash — 80×24"
        steps={[
          "Running setup...",
          "Creating the sea...",
          "Setting up the sand...",
          "Configuring the waves...",
          "Wiring up the shore...",
          "Unleashing the tides...",
        ]}
        finalMessage={`Welcome to 8995 Riptide!`}
        stepDelay={900}
        className="fixed inset-0 z-[9999] grid place-items-center bg-black/80 p-4"
      />
      <SiteHeader />
      <ScrollProgress/>
      <FollowingPointer
      label="You(viewer)"
    >

      <main>
        {/* Hero + live showcase */}
        <section className="relative overflow-hidden pt-28 pb-16 lg:pt-36">
          <AuroraBackground intensity="vivid" />
          <GridPattern
            width={48}
            height={48}
            className="fill-transparent stroke-border/60 mask-[radial-gradient(ellipse_70%_50%_at_30%_0%,black,transparent)]"
          />
          <div className="relative mx-auto grid max-w-7xl grid-cols-1 items-center gap-10 px-4 lg:grid-cols-2 lg:gap-12 lg:px-8">
            {/* Plain server HTML: the h1 and intro are the LCP. */}
            <div className="min-w-0">
              <AnimatedTooltip
      items={[
        { name: "Saiprasad Valada", role: "Lead Programmer and Designer" },
        { name: "Akshara Prasanna", role: "Lead Designer and Builder" },
        { name: "Oliver Hack", role: "Lead Builder and Designer" },
        { name: "Sailas de Kok", role: "Programmer and Builder" },
        { name: "Amaan Shaik", role: "Designer and Builder" },
      ]}
    />

              <h1 className="mt-6 text-4xl font-semibold tracking-tight text-balance sm:text-5xl xl:text-6xl">
                Welcome to{" "}
                <AnimatedGradientText className="bg-linear-to-r from-brand-from via-brand-via to-brand-to bg-clip-text text-transparent">
                  8995R Riptide
                </AnimatedGradientText>
              </h1>
              <p className="mt-5 max-w-xl text-lg text-muted-foreground text-pretty">
                The official site for all things {" "}
                <AnimatedGradientText>
        <Typewriter words={["designing.", "building.", "programming.", "8995Riptide."]} />
      </AnimatedGradientText>
              </p>

              <div className="mt-8 flex flex-wrap items-center gap-3">
                <ShimmerButton className="inline-flex h-11 items-center gap-2 px-6 text-sm font-medium text-background shadow-lg shadow-primary/20 transition-opacity hover:opacity-90">
                <Link
                  href="/#stats"
                >
                  
                  Browse stats
                </Link>
                </ShimmerButton>
                <MovingBorder className="inline-flex items-center">
                <Link
                  href={siteConfig.github}
                >
                  View repo
                </Link>
                </MovingBorder>
              </div>
            </div>
          </div>
        </section>

        {/* Stats */}
        <section aria-label="Velora in numbers" className="px-4 py-14 lg:px-8" id="stats">
          <div className="flex flex-wrap items-end justify-between gap-4 mx-auto max-w-6xl gap-px lg:grid-cols-4 gap-15 p-5">
              <SectionHeading
                id="stats"
                eyebrow="Stats"
                title="Our Stats"
              />

            </div>
            <TiltCard>  
          <dl className="mx-auto grid max-w-6xl grid-cols-2 gap-px overflow-hidden rounded-2xl border bg-border lg:grid-cols-4">
            
            {[
              { value: 2, label: "events" },
              { value: "5-3-0", label: "matches" },
              { value: 1.3, label: "Avg WP / Match" },
              { value: "63%", label: "Win Rate" },
            ].map((s) => (
              <div key={s.label} className="flex flex-col-reverse gap-1 bg-background p-6 lg:p-8">
                <dt className="text-sm text-muted-foreground">{s.label}</dt>
                <dd className="text-4xl font-semibold tracking-tight">{s.value}</dd>
              </div>
            ))}
          </dl>
          </TiltCard>
          
        </section>
        <section aria-label="Timeline" className="mx-auto max-w-6xl px-4 py-14 lg:px-8" id="timeline">
          <SectionHeading
                id="timeline"
                eyebrow="Timeline"
                title="Our Timeline"
              />
            <div className="p-5">
          <Timeline items={timeline}/>
          </div>
        </section>
        {/* Categories */}
        <section aria-labelledby="events" className="py-14 lg:py-20">
          <div className="mx-auto max-w-6xl px-4 lg:px-8">
            <div className="flex flex-wrap items-end justify-between gap-4">
              <div className={cn("max-w-2xl")}>
      <p className="text-sm font-medium text-primary">Events</p>
      <h2
        id="events"
        className="mt-2 text-3xl font-semibold tracking-tight text-balance lg:text-4xl"
      >
         <NumberTicker value={2}/> events
      </h2>
    </div>

            </div>
            <ul className="mt-8 grid grid-cols-2 gap-2.5 sm:grid-cols-3 lg:grid-cols-4">
              {events.map((event) => {
                const link = categoryIcons[event];
                return (
                  <li
                    key={event}
                    className="group/card relative flex items-center gap-3 rounded-xl border bg-card/50 p-3 transition-colors focus-within:ring-2 focus-within:ring-ring hover:border-primary/40"
                  >
                    <h3 className="min-w-0 flex-1 truncate text-sm font-medium">
                      <Link
                        href={link}
                        className="outline-none after:absolute after:inset-0 after:rounded-xl"
                      >
                        {event}
                      </Link>
                    </h3>
                  </li>
                );
              })}
            </ul>
          </div>
        </section>
                <section aria-label="Notes" className="px-4 py-14 lg:px-8" id="stats">
          <div className="flex flex-wrap items-end justify-between gap-4 mx-auto max-w-6xl gap-px lg:grid-cols-4 gap-15 p-5">
              <SectionHeading
                id="notes"
                eyebrow="Engineering Notebook"
                title="Our Engineering Notebook"
              />

            </div>
        <MarkdownDisplay />
        </section>
        {/* Blocks */}
        <section aria-labelledby="blocks" className="py-14 lg:py-20">
          <div className="mx-auto max-w-6xl px-4 lg:px-8">
            <div className="flex flex-wrap items-end justify-between gap-4">
              <SectionHeading id="cad" eyebrow="CAD" title="Our CAD models, free" />
            </div>
            <ul className="mt-8 grid gap-4 sm:grid-cols-2 lg:grid-cols-4">
                <li
                  className="group/card relative min-w-0 overflow-hidden rounded-2xl border bg-card/50 transition-all focus-within:ring-2 focus-within:ring-ring hover:-translate-y-0.5 hover:shadow-lg hover:shadow-primary/5"
                >
                  <div className="border-b">
                        <div
      aria-hidden
      className="relative aspect-[16/10] overflow-hidden bg-background"
    >

<iframe width="260" height="160" src="https://3dviewer.net/embed.html#model=https://pub-00a1ddf6905e4f7bb0d5cd4859c09c8c.r2.dev/drivetrain-Assembly.glb"></iframe>
    </div>
                  </div>
                  <div className="p-4">
                    <h3 className="text-sm font-medium">
                      <Link href="https://pub-00a1ddf6905e4f7bb0d5cd4859c09c8c.r2.dev/drivetrain-Assembly.glb">
                        Drivetrain CAD
                        </Link>
                    </h3> 
                  </div>
                </li>
                <li
                  className="group/card relative min-w-0 overflow-hidden rounded-2xl border bg-card/50 transition-all focus-within:ring-2 focus-within:ring-ring hover:-translate-y-0.5 hover:shadow-lg hover:shadow-primary/5"
                >
                  <div className="border-b">
                        <div
      aria-hidden
      className="relative aspect-[16/10] overflow-hidden bg-background"
    >
      
<iframe width="260" height="160" src="https://3dviewer.net/embed.html#model=https://pub-00a1ddf6905e4f7bb0d5cd4859c09c8c.r2.dev/dr4bp1-Assembly.glb"></iframe>
    </div>
                  </div>
                  <div className="p-4">
                    <h3 className="text-sm font-medium">
                      <Link href="https://pub-00a1ddf6905e4f7bb0d5cd4859c09c8c.r2.dev/dr4bp1-Assembly.glb">
                        DR4B CAD
                      </Link>
                    </h3> 
                  </div>
                </li>
            </ul>
          </div>
        </section>
        {/* Install */}
        <section aria-labelledby="install" className="py-14 lg:py-20">
          <div className="mx-auto grid max-w-6xl grid-cols-1 gap-10 px-4 lg:grid-cols-5 lg:gap-16 lg:px-8">
            <div className="lg:col-span-2">
              <SectionHeading id="repo" eyebrow="Our repo" title="Install in seconds" />
            </div>
            <TerminalView
      className="min-w-0 space-y-6 lg:col-span-3"
      lines={[
        "1. Clone the repo",
        "$ git clone https://github.com/8995riptide/robot-code.git",
        "2. Navigate to the project directory",
        "$ cd robot-code",
        "3. View CAD models",
        "$ cd designs && <software> <model-file>",
        "4. View code",
        "$ <software> ../code/src/main.cpp",
        "4. View notes",
        "$ cd ../notes && <software> <note-file>",
      ]}
    />
          </div>
        </section>
      </main>
      </FollowingPointer>
      <SiteFooter />
    </>
  );
}
