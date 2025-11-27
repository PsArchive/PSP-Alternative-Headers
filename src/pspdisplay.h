/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspdisplay.h - Prototypes for the sceDisplay and sceDisplay_driver libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 */
#ifndef __DISPLAY_H__
#define __DISPLAY_H__
// Protect from double definition of mixing our modified header with pspsdk header
#define __DISPLAYKERNEL_H__

/** Framebuffer pixel formats. */
enum SceDisplayPixelFormats {
	/** 16-bit RGB 5:6:5. */
	SCE_DISPLAY_PIXEL_FORMAT_565 = 0,
	/** 16-bit RGBA 5:5:5:1. */
	SCE_DISPLAY_PIXEL_FORMAT_5551 = 1,
	/* 16-bit RGBA 4:4:4:4. */
	SCE_DISPLAY_PIXEL_FORMAT_4444 = 2,
	/* 32-bit RGBA 8:8:8:8. */
	SCE_DISPLAY_PIXEL_FORMAT_8888 = 3,

	/** 16-bit RGB 5:6:5. */
	PSP_DISPLAY_PIXEL_FORMAT_565 = SCE_DISPLAY_PIXEL_FORMAT_565,
	/** 16-bit RGBA 5:5:5:1. */
	PSP_DISPLAY_PIXEL_FORMAT_5551 = SCE_DISPLAY_PIXEL_FORMAT_5551,
	/* 16-bit RGBA 4:4:4:4. */
	PSP_DISPLAY_PIXEL_FORMAT_4444 = SCE_DISPLAY_PIXEL_FORMAT_4444,
	/* 32-bit RGBA 8:8:8:8. */
	PSP_DISPLAY_PIXEL_FORMAT_8888 = SCE_DISPLAY_PIXEL_FORMAT_8888,
};

enum SceDisplaySetBufSync {
	/** Buffer change effective next hsync */
	SCE_DISPLAY_SETBUF_NEXTHSYNC = 0,
	/** Buffer change effective next vsync */
	SCE_DISPLAY_SETBUF_NEXTVSYNC = 1,

	/** Buffer change effective next hsync */
	PSP_DISPLAY_SETBUF_NEXTHSYNC = SCE_DISPLAY_SETBUF_NEXTHSYNC,
	/** Buffer change effective next vsync */
	PSP_DISPLAY_SETBUF_NEXTVSYNC = SCE_DISPLAY_SETBUF_NEXTVSYNC,
};

/** Values for retro compatibility */
#define PSP_DISPLAY_SETBUF_IMMEDIATE PSP_DISPLAY_SETBUF_NEXTHSYNC
#define PSP_DISPLAY_SETBUF_NEXTFRAME PSP_DISPLAY_SETBUF_NEXTVSYNC

enum SceDisplayMode {
	/** LCD MAX 480x272 at 59.94005995 Hz */
	SCE_DISPLAY_MODE_LCD = 0,
	/** VESA VGA MAX 640x480 at 59.94047618Hz */
	SCE_DISPLAY_MODE_VESA1A = 0x1A,
	/** PSEUDO VGA MAX 640x480 at 59.94005995Hz*/
	SCE_DISPLAY_MODE_PSEUDO_VGA = 0x60,

	/** LCD MAX 480x272 at 59.94005995 Hz */
	PSP_DISPLAY_MODE_LCD = SCE_DISPLAY_MODE_LCD,
	/** VESA VGA MAX 640x480 at 59.94047618Hz */
	PSP_DISPLAY_MODE_VESA1A = SCE_DISPLAY_MODE_VESA1A,
	/** PSEUDO VGA MAX 640x480 at 59.94005995Hz*/
	PSP_DISPLAY_MODE_PSEUDO_VGA = SCE_DISPLAY_MODE_PSEUDO_VGA,
};

enum PspDisplayErrorCodes {
	SCE_DISPLAY_ERROR_OK = 0,
	SCE_DISPLAY_ERROR_POINTER = 0x80000103,
	SCE_DISPLAY_ERROR_ARGUMENT = 0x80000107
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Set display mode
 *
 * @par Example1:
 * @code
 * int mode = PSP_DISPLAY_MODE_LCD;
 * int width = 480;
 * int height = 272;
 * sceDisplaySetMode(mode, width, height);
 * @endcode
 *
 * @param mode The mode to set. One of `SceDisplayMode`.
 * @param width The width of screen in pixels.
 * @param height The height of screen in pixels.
 *
 * @return When error, a negative value is returned.
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplaySetMode(int mode, int width, int height);

/**
 * Get display mode
 *
 * @param[out] mode A pointer to an integer to receive the current mode.
 * @param[out] width A pointer to an integer to receive the current width.
 * @param[out] height A pointer to an integer to receive the current height.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayGetMode(int *mode, int *width, int *height);

/**
 * Sets a framebuf to be e used to display.
 *
 * @param[in] buf_addr The address of the start of framebuffer
 * @param buf_width The buffer width (must be power of 2)
 * @param pixel_format The pixel format to use. One of `SceDisplayPixelFormats`.
 * @param sync The sync policy to use. One of `SceDisplaySetBufSync`
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplaySetFrameBuf(void *buf_addr, int buf_width, int pixel_format, int sync);

/**
 * Get Display Framebuffer information
 *
 * @param[out] buf_addr A pointer to void* to receive address of start of framebuffer
 * @param[out] buf_width A pointer to int to receive buffer width (must be power of 2)
 * @param[out] pixel_format A pointer to int to receive one of `SceDisplayPixelFormats`.
 * @param sync The sync policy. One of `SceDisplaySetBufSync`
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayGetFrameBuf(void **buf_addr, int *buf_width, int *pixel_format, int sync);

/**
 * Number of vertical blank pulses up to now
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
unsigned int sceDisplayGetVcount(void);

/**
 * Wait for vertical blank start
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayWaitVblankStart(void);

/**
 * Wait for vertical blank start with callback
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayWaitVblankStartCB(void);

/**
 * Wait for vertical blank
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayWaitVblank(void);

/**
 * Wait for vertical blank with callback
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayWaitVblankCB(void);

/**
 * Get accumlated HSYNC count
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayGetAccumulatedHcount(void);

/**
 * Get current HSYNC count
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayGetCurrentHcount(void);

/**
 * Get number of frames per second
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
float sceDisplayGetFramePerSec(void);

/**
 * Get whether or not frame buffer is being displayed
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayIsForeground(void);

/**
 * Test whether VBLANK is active
 *
 * @attention Requires linking to `pspdisplay` (PSPSDK), `pspdisplay_user` (Adrenaline stubs)  or `pspdisplay_driver` stubs to be available.
 */
int sceDisplayIsVblank(void);


#ifdef __KERNEL__

/**
 * Set Display brightness to a particular level.
 *
 * @param level The level of the brightness. it goes from `0` (black screen) to `100` (max brightness).
 * @param unk1 Unknown. It can be `0` or `1` (pass `0`).
 *
 * @attention Requires linking to `pspdisplay_driver` stub to be available.
 */
void sceDisplaySetBrightness(int level,int unk1);

/**
 * Get current display brightness.
 *
 * @param[out] level A pointer to int to receive the current brightness level (`0-100`).
 * @param[out] unk1 A pointer to int, receives unknown, it's `1` or `0`.
 *
 * @attention Requires linking to `pspdisplay_driver` stub to be available.
 */
void sceDisplayGetBrightness(int *level,int *unk1);


#ifdef _USE_PSPSDK_STUB

/**
 * Sets the display framebuffer
 *
 * @param priority The priority for the framebuffer.
 * @param buf_addr The address of start of framebuffer.
 * @param buf_width The buffer width (must be power of 2).
 * @param pixel_format The pixel format to use. One of `PspDisplayPixelFormats`.
 * @param sync The sync policy to use. One of `PspDisplaySetBufSync`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay_driver` stub to be available.
 */
int sceDisplay_driver_63E22A26(int priority, void *buf_addr, int buf_width, int pixel_format, int sync);
#define sceDisplay_driver_3E17FE8D sceDisplay_driver_63E22A26
#define sceDisplaySetFrameBufferInternal sceDisplay_driver_63E22A26

/**
 * Get Display Framebuffer information
 *
 * @param priority The priority for the framebuffer.
 * @param[out] buf_addr A pointer to void* to receive address of start of framebuffer
 * @param[out] buf_width A pointer to int to receive buffer width (must be power of 2)
 * @param[out] pixel_format A pointer to int to receive one of `SceDisplayPixelFormats`.
 * @param[out] sync The sync policy. One of `SceDisplaySetBufSync`
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay_driver` stub to be available.
 */
int sceDisplay_driver_5B5AEFAD(int priority, void **buf_addr, int *buf_width, int *pixel_format, int *sync);
#define sceDisplay_driver_F338AAE0 sceDisplay_driver_5B5AEFAD
#define sceDisplayGetFrameBufferInternal sceDisplay_driver_5B5AEFAD

#else /* ADRENALINE STUBS (6.61) */

/**
 * Sets the display framebuffer
 *
 * @param priority The priority for the framebuffer.
 * @param buf_addr The address of start of framebuffer.
 * @param buf_width The buffer width (must be power of 2).
 * @param pixel_format The pixel format to use. One of `PspDisplayPixelFormats`.
 * @param sync The sync policy to use. One of `PspDisplaySetBufSync`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay_driver` stub to be available.
 */
int sceDisplay_driver_3E17FE8D(int priority, void *buf_addr, int buf_width, int pixel_format, int sync);
#define sceDisplay_driver_63E22A26 sceDisplay_driver_3E17FE8D
#define sceDisplaySetFrameBufferInternal sceDisplay_driver_3E17FE8D

/**
 * Get Display Framebuffer information
 *
 * @param priority The priority for the framebuffer.
 * @param[out] buf_addr A pointer to void* to receive address of start of framebuffer
 * @param[out] buf_width A pointer to int to receive buffer width (must be power of 2)
 * @param[out] pixel_format A pointer to int to receive one of `SceDisplayPixelFormats`.
 * @param[out] sync The sync policy. One of `SceDisplaySetBufSync`
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspdisplay_driver` stub to be available.
 */
int sceDisplay_driver_F338AAE0(int priority, void **buf_addr, int *buf_width, int *pixel_format, int *sync);
#define sceDisplay_driver_5B5AEFAD sceDisplay_driver_F338AAE0
#define sceDisplayGetFrameBufferInternal sceDisplay_driver_F338AAE0

#endif // _USE_PSPSDK_STUB

#endif // __KERNEL__


#ifdef __cplusplus
}
#endif // __cplusplus

#endif
