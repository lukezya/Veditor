# Veditor

Veditor is a software tool aimed at Twitch streamers who broadcast video games. The project addresses the challenge of creating highlight videos from Twitch streams, as viewers often miss valuable moments during lengthy broadcasts. The goal of Veditor is to automatically process Twitch video streams, extract game metadata using optical character recognition (OCR), and generate separate highlight videos for each game played in the stream.

## Features

- Download Twitch stream videos using the youtube-dl library.
- Extract image frames from videos using the ffmpeg library.
- Preprocess images to enhance readability of text using the opencv library.
- Utilize OCR technology with the Tesseract library to extract text from images.
- Parse OCR results to identify time lengths of highlights in C++.
- Clip highlight segments from the original video using the ffmpeg library.
- Merge all highlight clips into a single highlight video using the ffmpeg library.
