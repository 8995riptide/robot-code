/**
 * Single source of truth for external URLs. Override at build time with
 * NEXT_PUBLIC_SITE_URL / NEXT_PUBLIC_GITHUB_URL when the real domain and
 * repo are wired up.
 */
export const siteConfig = {
  name: "8995 Riptide",
  url: (
    process.env.NEXT_PUBLIC_SITE_URL ?? "https://8995riptide.vercel.app"
  ).replace(/\/$/, ""),
  github:
    process.env.NEXT_PUBLIC_GITHUB_URL ??
    "https://github.com/8995riptide/robot-code",
  /** Velora Pro is sold through dashboardpack.com (WooCommerce product 393469). */
  pro: {
    /**
     * Flip to true once product 393469 is published on dashboardpack.com
     * (and the Club Pass includes the zip). Until then Pro shows a waitlist,
     * because cart links to a draft product fail.
     */
    onSale: false,
    personal: {
      price: 149,
      checkout:
        "https://dashboardpack.com/cart/?add-to-cart=393469&variation_id=393470",
    },
    /** Blocks + every template, current and future */
    allAccess: {
      price: 249,
      checkout:
        "https://dashboardpack.com/cart/?add-to-cart=393469&variation_id=393485",
    },
    /** All-Access for up to 10 developers */
    team: {
      price: 399,
      checkout:
        "https://dashboardpack.com/cart/?add-to-cart=393469&variation_id=393471",
    },
    clubPass: "https://dashboardpack.com/lifetime-club-pass/",
  },
  tagline: "The website for everything 8995Riptide",
  description:
    "The official website for the 8995 Riptide robotics team, showcasing our projects, competitions, and engineering notes.",
} as const;
