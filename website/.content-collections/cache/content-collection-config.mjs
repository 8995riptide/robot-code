// content-collections.ts
import { defineCollection, defineConfig } from "@content-collections/core";
import { z } from "zod";
var notes = defineCollection({
  name: "notes",
  directory: "../notes",
  include: "**/*.md",
  schema: z.object({
    title: z.string().optional(),
    summary: z.string().optional(),
    week: z.coerce.number(),
    content: z.string()
  })
});
var content_collections_default = defineConfig({
  content: [notes]
});
export {
  content_collections_default as default
};
