# Media

Concept preview assets for the dual-wheel **Q1** (G1-Edu-style developer teaser).

| File | Use |
|------|-----|
| `q1_wheeled_concept_demo.gif` | README autoplay preview |
| `q1_wheeled_concept_demo.mp4` | Full HTML5 / download playback |
| `q1_wheeled_concept_poster.png` | Video poster frame |

Regenerate:

```bash
python3 scripts/generate_concept_demo.py
ffmpeg -y -framerate 24 -i media/demo_frames/frame_%04d.png \
  -c:v libx264 -pix_fmt yuv420p -crf 23 -movflags +faststart \
  media/q1_wheeled_concept_demo.mp4
```
