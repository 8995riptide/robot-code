"use client";
import React, { useState, useMemo, useEffect } from 'react';
import Box from '@mui/material/Box';
import Slider from '@mui/material/Slider';
import MarkdownPreview from '@uiw/react-markdown-preview';
import rehypeSanitize, { defaultSchema } from 'rehype-sanitize';
import { allNotes } from 'content-collections';
import List from '@mui/material/List';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemText from '@mui/material/ListItemText';
function valuetext(value: number) {
  return `Week ${value}`;
}

export default function MarkdownDisplay() {
    const customSchema = {
  ...defaultSchema,
  tagNames: [...(defaultSchema.tagNames || []), 'iframe'],
  attributes: {
    ...defaultSchema.attributes,
    iframe: ['src', 'width', 'height', 'style', 'title', 'allowFullScreen', 'frameBorder'],
  },
};
    const availableWeeks = useMemo(() => {
        const unique = Array.from(new Set(allNotes.map(note => note.week)));
        return unique.length > 0 ? unique.sort((a, b) => a - b) : [1];
    }, []);
    const [week, setWeek] = useState<number>(availableWeeks[0]);
    const [selectedPath, setSelectedPath] = useState<string>("");
    const currentNotes = useMemo(() => allNotes.filter((note) => note.week === week), [week]);
    useEffect(() => {
        if (currentNotes.length > 0) {
            setSelectedPath(currentNotes[0]._meta.path);
        }
    }, [currentNotes, week]);
    const activeNote = useMemo(() => currentNotes.find((note) => note._meta.path === selectedPath), [currentNotes, selectedPath]);
    const marks = availableWeeks.map((w) => ({ value: w, label: `Week ${w}` }));
    
    return (
        <Box sx={{ width: '50%', display: "grid", gridTemplateColumns: { xs: "1fr", md: currentNotes.length > 1 ? "280px minmax(0, 1fr)" : "minmax(0, 1fr)" }, gap: 4, alignItems: "start", mx: "auto" }}>
            {currentNotes.length > 1 && (
            <Box>
                <div className="border rounded-lg p-2">
                    <p className="text-xs font-semibold uppercase text-muted-foreground px-3 py-2">
                      Week {week}   
                    </p>
                <List dense disablePadding>
                    {currentNotes.map((note) => (
                        <ListItemButton key={note._meta.path} onClick={() => setSelectedPath(note._meta.path)}>
                            <ListItemText primary={note.title} />
                        </ListItemButton>
                    ))}
                </List>
                          </div>
            
            </Box>
            )}
            <Box sx={{ width: '100%', mx: "auto" }}>
            <Box sx={{ width: 300, mx: "auto" }}>
                <Slider
        aria-label="Custom marks"
        value={week}
        onChange={(event, newValue) => setWeek(newValue as number)}
        getAriaValueText={valuetext}
        step={1}
        shiftStep={1}
        min={1}
        max={availableWeeks[availableWeeks.length - 1]}
        valueLabelDisplay="auto"
        marks={marks}
          sx={{
    "& .MuiSlider-markLabel": {
      color: "#fff",
    },
    "& .MuiSlider-markLabelActive": {
      color: "#fff",
    },
    mx: "auto"
  }}
      />
      </Box>
        <Box sx={{ width: '100%', mx: "auto" }}>
        <div className="space-y-6">
            {activeNote && (
                <div key={activeNote._meta.path} className="p-5 border rounded-lg">
                <h3 className="text-lg font-semibold">{activeNote.title}</h3>
                <p className="text-sm text-muted-foreground mb-4">{activeNote.summary}</p>
                <MarkdownPreview source={activeNote.content} rehypePlugins={[[rehypeSanitize, customSchema]]} />
                </div>
            )}
        </div>
        </Box>
        </Box>
        </Box>
    )
}