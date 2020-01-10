/* ANSI-C code produced by gperf version 3.0.4 */
/* Command-line: gperf  */
/* Computed positions: -k'1,3' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

struct tag_data { gint name; guint etag; };
#include <string.h>

#define TOTAL_KEYWORDS 47
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 22
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 80
/* maximum key range = 77, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
as_tag_hash (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 60, 20,  0,
      15, 50, 81, 25, 81, 15, 81, 30, 15,  5,
      15, 25,  5, 81, 10, 10,  0, 30,  0, 81,
      81, 15, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81, 81, 81, 81, 81,
      81, 81, 81, 81, 81, 81
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

struct stringpool_t
  {
    char stringpool_str4[sizeof("veto")];
    char stringpool_str5[sizeof("vetos")];
    char stringpool_str8[sizeof("category")];
    char stringpool_str10[sizeof("categories")];
    char stringpool_str12[sizeof("caption")];
    char stringpool_str13[sizeof("metadata")];
    char stringpool_str14[sizeof("component")];
    char stringpool_str15[sizeof("components")];
    char stringpool_str17[sizeof("id")];
    char stringpool_str18[sizeof("mimetype")];
    char stringpool_str19[sizeof("mimetypes")];
    char stringpool_str20[sizeof("value")];
    char stringpool_str21[sizeof("metadata_license")];
    char stringpool_str22[sizeof("summary")];
    char stringpool_str23[sizeof("location")];
    char stringpool_str24[sizeof("name")];
    char stringpool_str25[sizeof("permission")];
    char stringpool_str26[sizeof("permissions")];
    char stringpool_str27[sizeof("compulsory_for_desktop")];
    char stringpool_str28[sizeof("priority")];
    char stringpool_str29[sizeof("developer_name")];
    char stringpool_str30[sizeof("screenshot")];
    char stringpool_str31[sizeof("screenshots")];
    char stringpool_str32[sizeof("release")];
    char stringpool_str33[sizeof("releases")];
    char stringpool_str34[sizeof("lang")];
    char stringpool_str36[sizeof("description")];
    char stringpool_str37[sizeof("pkgname")];
    char stringpool_str38[sizeof("provides")];
    char stringpool_str39[sizeof("languages")];
    char stringpool_str41[sizeof("bundle")];
    char stringpool_str43[sizeof("project_group")];
    char stringpool_str44[sizeof("icon")];
    char stringpool_str45[sizeof("project_license")];
    char stringpool_str48[sizeof("url")];
    char stringpool_str49[sizeof("kudo")];
    char stringpool_str50[sizeof("kudos")];
    char stringpool_str52[sizeof("keyword")];
    char stringpool_str53[sizeof("keywords")];
    char stringpool_str54[sizeof("source_pkgname")];
    char stringpool_str57[sizeof("extends")];
    char stringpool_str58[sizeof("checksum")];
    char stringpool_str59[sizeof("update_contact")];
    char stringpool_str64[sizeof("arch")];
    char stringpool_str67[sizeof("unknown")];
    char stringpool_str73[sizeof("architectures")];
    char stringpool_str80[sizeof("image")];
  };
static const struct stringpool_t stringpool_contents =
  {
    "veto",
    "vetos",
    "category",
    "categories",
    "caption",
    "metadata",
    "component",
    "components",
    "id",
    "mimetype",
    "mimetypes",
    "value",
    "metadata_license",
    "summary",
    "location",
    "name",
    "permission",
    "permissions",
    "compulsory_for_desktop",
    "priority",
    "developer_name",
    "screenshot",
    "screenshots",
    "release",
    "releases",
    "lang",
    "description",
    "pkgname",
    "provides",
    "languages",
    "bundle",
    "project_group",
    "icon",
    "project_license",
    "url",
    "kudo",
    "kudos",
    "keyword",
    "keywords",
    "source_pkgname",
    "extends",
    "checksum",
    "update_contact",
    "arch",
    "unknown",
    "architectures",
    "image"
  };
#define stringpool ((const char *) &stringpool_contents)
#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct tag_data *
as_tag_from_gperf (register const char *str, register unsigned int len)
{
  static const struct tag_data wordlist[] =
    {
      {-1}, {-1}, {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str4, AS_TAG_VETO},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str5, AS_TAG_VETOS},
      {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str8, AS_TAG_CATEGORY},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str10, AS_TAG_CATEGORIES},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str12, AS_TAG_CAPTION},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str13, AS_TAG_METADATA},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str14, AS_TAG_APPLICATION},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str15, AS_TAG_APPLICATIONS},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str17, AS_TAG_ID},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str18, AS_TAG_MIMETYPE},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str19, AS_TAG_MIMETYPES},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str20, AS_TAG_VALUE},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str21, AS_TAG_METADATA_LICENSE},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str22, AS_TAG_SUMMARY},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str23, AS_TAG_LOCATION},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str24, AS_TAG_NAME},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str25, AS_TAG_PERMISSION},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str26, AS_TAG_PERMISSIONS},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str27, AS_TAG_COMPULSORY_FOR_DESKTOP},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str28, AS_TAG_PRIORITY},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str29, AS_TAG_DEVELOPER_NAME},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str30, AS_TAG_SCREENSHOT},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str31, AS_TAG_SCREENSHOTS},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str32, AS_TAG_RELEASE},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str33, AS_TAG_RELEASES},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str34, AS_TAG_LANG},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str36, AS_TAG_DESCRIPTION},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str37, AS_TAG_PKGNAME},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str38, AS_TAG_PROVIDES},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str39, AS_TAG_LANGUAGES},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str41, AS_TAG_BUNDLE},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str43, AS_TAG_PROJECT_GROUP},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str44, AS_TAG_ICON},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str45, AS_TAG_PROJECT_LICENSE},
      {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str48, AS_TAG_URL},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str49, AS_TAG_KUDO},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str50, AS_TAG_KUDOS},
      {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str52, AS_TAG_KEYWORD},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str53, AS_TAG_KEYWORDS},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str54, AS_TAG_SOURCE_PKGNAME},
      {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str57, AS_TAG_EXTENDS},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str58, AS_TAG_CHECKSUM},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str59, AS_TAG_UPDATE_CONTACT},
      {-1}, {-1}, {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str64, AS_TAG_ARCH},
      {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str67, AS_TAG_UNKNOWN},
      {-1}, {-1}, {-1}, {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str73, AS_TAG_ARCHITECTURES},
      {-1}, {-1}, {-1}, {-1}, {-1}, {-1},
      {(int)(long)&((struct stringpool_t *)0)->stringpool_str80, AS_TAG_IMAGE}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = as_tag_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int o = wordlist[key].name;
          if (o >= 0)
            {
              register const char *s = o + stringpool;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[key];
            }
        }
    }
  return 0;
}
