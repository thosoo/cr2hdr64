# Dual ISO

- Author: a1ex
- License: GPL
- Summary: Dynamic range improvement by using two ISOs in one picture
- Forum: http://www.magiclantern.fm/forum/index.php?topic=7139.0

Increases dynamic range by sampling the sensor at two different ISOs, switching ISO for every other line pair.
This trick cleans up shadow noise, resulting in a dynamic range improvement of around 3 stops,
at the cost of reduced vertical resolution, aliasing and moire.

Works for both raw photos (CR2) and raw videos (DNG). You need to postprocess these files with a tool called **cr2hdr**.

After postprocessing, you will get a DNG that looks like a dark ISO 100 shot,
but you can bring the exposure back up and be delighted by how little noise is present in those recovered shadows.

## Quick start

* Start at ISO 100 in Canon menu
* Expose to the right by changing shutter and aperture
* If the image is still dark, enable dual ISO
* Adjust recovery ISO: higher values = cleaner shadows, but more artifacts
* Try not to go past ISO 1600; you will not see any major improvements, 
  but you will get more interpolation artifacts and hot pixels.

## Tips and tricks

* Do not use dual ISO for regular scenes that don't require a very high dynamic range.
* Raw zebras are aware of dual ISO: weak zebras are displayed where only the high ISO is overexposed,
  strong (solid) zebras are displayed where both ISOs are overexposed.
* Raw histogram will display only the low-ISO half of the image (since the high-ISO data is used
  for cleaning up shadow noise).
* For optimal exposure (minimal noise without clipped highlights), try both dual ISO and ETTR.
* Do not be afraid of less aggressive settings like 100/400. They are almost as good as 100/1600 
  regarding shadow noise, but with much less aliasing artifacts.
* Be careful with long exposures, you may get lots of hot pixels.

## Build and install

``` sh
make
sudo make install
```

## Using cr2hdr

``` sh
cr2hdr: a post processing tool for Dual ISO images

No input files.

GUI usage: drag some CR2 or DNG files over cr2hdr.exe.

Command-line usage: cr2hdr [OPTIONS] [FILES]

Shortcuts:
--fast          : disable most postprocessing steps (fast, but low quality)
                  (--mean23, --no-cs, --no-fullres, --no-alias-map, --no-stripe-fix, --no-bad-pix)

Interpolation methods:
--amaze-edge    : use a temporary demosaic step (AMaZE) followed by edge-directed interpolation (default)
--mean23        : average the nearest 2 or 3 pixels of the same color from the Bayer grid (faster)

Chroma smoothing:
--cs2x2         : apply 2x2 chroma smoothing in noisy and aliased areas (default)
--cs3x3         : apply 3x3 chroma smoothing in noisy and aliased areas
--cs5x5         : apply 5x5 chroma smoothing in noisy and aliased areas
--no-cs         : disable chroma smoothing

Bad pixel handling:
--really-bad-pix: aggressive bad pixel fix, at the expense of detail and aliasing
--no-bad-pix    : disable bad pixel fixing (try it if you shoot stars)
--black-bad-pix : mark all bad pixels as black (for troubleshooting)

Highlight/shadow handling:
--soft-film=%f  : bake a soft-film curve to compress highlights and raise shadows by X EV
                  (if you use this option, you should also specify the white balance)

White balance:
--wb=graymax    : set AsShotNeutral by maximizing the number of gray pixels (default)
--wb=graymed    : set AsShotNeutral from the median of R-G and B-G
--wb=exif       : set AsShotNeutral from EXIF WB (not exactly working)
--wb=%f,%f,%f   : use custom RGB multipliers

Other postprocessing steps:
--no-fullres    : disable full-resolution blending
--no-alias-map  : disable alias map, used to fix aliasing in deep shadows
--no-stripe-fix : disable horizontal stripe fix

Flicker handling:
--same-levels   : Adjust output white levels to keep the same overall exposure
                  for all frames passed in a single command line
                  (useful to avoid flicker - for video or panoramas)

DNG compression (requires Adobe DNG Converter):
--compress      : Lossless DNG compression
--compress-lossy: Lossy DNG compression (be careful, may destroy shadow detail)

Misc settings:
--skip-existing : Skip the conversion if the output file already exists
--embed-original: Embed (move) the original CR2 file in the output DNG. The original will be deleted.
                  You will be able to re-process the DNG with a different version or different conversion settings.
                  To recover the original: exiftool IMG_1234.DNG -OriginalRawFileData -b > IMG_1234.CR2
--embed-original-copy: 
                  Similar to --embed-original, but without deleting the original.


Troubleshooting options:
--force         : force processing even if the image is not Dual ISO.
--debug-blend   : save intermediate images used for blending:
    dark.dng        the low-ISO exposure, interpolated
    bright.dng      the high-ISO exposure, interpolated and darkened
    delta.dng       difference between the two (useful to check exposure matching)
    halfres.dng     half-resolution blending (low noise, high aliasing)
    fullres.dng     full-resolution blending (minimal aliasing, high noise)
    *_smooth.dng    images after chroma smoothing
--debug-black   : save intermediate images used for black level subtraction
--debug-amaze   : save AMaZE input and output
--debug-edge    : save debug info from edge-directed interpolation
--debug-alias   : save debug info about the alias map
--debug-rggb    : plot debug info for RGGB/BGGR autodetection (requires octave)
--debug-bddb    : plot debug info for bright/dark autodetection (requires octave)
--debug-wb      : show the vectorscope used for white balance (requires octave)
--iso-curve     : plot the curve fitting results for ISO and black offset (requires octave)
--mix-curve     : plot the curve used for half-res blending (requires octave)
--fullres-curve : plot the curve used for full-res blending (requires octave)
```

## Run with multiple threads
A script has been added to run this with multiple threads.
``` sh
./run_parallel.sh directory/of/cr2 threads
```