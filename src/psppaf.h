/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psppaf.h - Prototypes for the scePaf library.
 *
 * Copyright (c) 2025 GrayJack
 *
 */

#ifndef __PSP_PAF_H_
#define __PSP_PAF_H_

#include <psptypes.h>

typedef struct {
	u8 id;
	u8 type;
	u16 unk1;
	u32 label;
	u32 param;
	u32 first_child;
	int child_count;
	u32 next_entry;
	u32 prev_entry;
	u32 parent;
	u32 unknown[2];
} SceRcoEntry;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __USER__

#define paf_free sce_paf_private_free
#define paf_malloc sce_paf_private_malloc
#define paf_memcpy sce_paf_private_memcpy
#define paf_memset sce_paf_private_memset
#define paf_snprintf sce_paf_private_snprintf
#define paf_sprintf sce_paf_private_sprintf
#define paf_strcasecmp sce_paf_private_strcasecmp
#define paf_strchr sce_paf_private_strchr
#define paf_strcmp sce_paf_private_strcmp
#define paf_strcpy sce_paf_private_strcpy
#define paf_strlen sce_paf_private_strlen
#define paf_strncasecmp sce_paf_private_strncasecmp
#define paf_strncmp sce_paf_private_strncmp
#define paf_strncpy sce_paf_private_strncpy
#define paf_strpbrk sce_paf_private_strpbrk
#define paf_strrchr sce_paf_private_strrchr
#define paf_strtoul sce_paf_private_strtoul
#define paf_wcslen sce_paf_private_wcslen

char *sce_paf_private_strchr(const char *, int);
char *sce_paf_private_strcpy(char *, const char *);
char *sce_paf_private_strncpy(char *, const char *, int);
char *sce_paf_private_strrchr(const char *, int);
int sce_paf_private_snprintf(char *, SceSize, const char *, ...);
int sce_paf_private_sprintf(char *, const char *, ...);
int sce_paf_private_strcasecmp(const char *, const char *);
int sce_paf_private_strcmp(const char *, const char *);
int sce_paf_private_strlen(char *);
int sce_paf_private_strncasecmp(const char *, const char *, SceSize);
int sce_paf_private_strncmp(const char *, const char *, int);
int sce_paf_private_strpbrk(const char *, const char *);
int sce_paf_private_strtoul(const char *, char **, int);
int sce_paf_private_wcslen(wchar_t *);
void *sce_paf_private_malloc(int);
void *sce_paf_private_memcpy(void *, void *, int);
void *sce_paf_private_memset(void *, char, int);
void sce_paf_private_free(void *);

// TODO: Add more `sce_paf_private` functions


int PAF_Resource_GetPageNodeByID(void *, char *, SceRcoEntry **);
int PAF_Resource_ResolveRefWString(void *, u32 *, int *, char **, int *);

/* Functions with popular naming */

wchar_t *scePafGetText(void *, char *);

#endif /* __USER__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSP_PAF_H_ */