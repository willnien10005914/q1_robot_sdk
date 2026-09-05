#!/usr/bin/env python3
"""Q1 wheeled concept demo — regenerate helper.

Shipped assets (do not delete):
  media/q1_wheeled_concept_demo.gif
  media/q1_wheeled_concept_demo.mp4
  media/q1_wheeled_concept_poster.png

The checked-in demo was rendered as a G1-Edu-style concept preview covering:
  01 wheeled locomotion, 02 piano, 03 calligraphy, 04 soft baseball.

To rebuild from frames (if you restore media/demo_frames/):

  ffmpeg -y -framerate 24 -i media/demo_frames/frame_%04d.png \\
    -c:v libx264 -pix_fmt yuv420p -crf 23 -movflags +faststart \\
    media/q1_wheeled_concept_demo.mp4

  ffmpeg -y -i media/q1_wheeled_concept_demo.mp4 \\
    -vf "fps=12,scale=960:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" \\
    media/q1_wheeled_concept_demo.gif
"""

if __name__ == "__main__":
    print(__doc__)
