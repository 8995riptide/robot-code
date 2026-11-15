import { defineCollection, defineConfig } from "@content-collections/core";
import { z } from "zod";
 
const notes = defineCollection({
  name: "notes",
  directory: "../notes",
  include: "**/*.md",
  schema: z.object({
    title: z.string().optional(),
    summary: z.string().optional(),
    week: z.coerce.number(),
    content: z.string(),
  }),
});
 
export default defineConfig({
  content: [notes],
});