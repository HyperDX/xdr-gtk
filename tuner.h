#ifndef XDR_TUNER_H_
#define XDR_TUNER_H_
#ifdef G_OS_WIN32
#include <windows.h>
#endif

// RDS
#define BLOCK_B 0
#define BLOCK_C 1
#define BLOCK_D 2

#define MODE_FM 0
#define MODE_AM 1
#define DEBUG_READ  0
#define DEBUG_WRITE 0
#define SERIAL_BUFFER 10000
#define FILTERS_N 30

#define TUNER_FREQ_MIN 100
#define TUNER_FREQ_MAX 200000

#define FREQ_MODIFY_DOWN  0
#define FREQ_MODIFY_UP    1
#define FREQ_MODIFY_RESET 2

typedef struct tuner
{
#ifdef G_OS_WIN32
    HANDLE serial;
    SOCKET socket;
#else
    gint serial;
#endif

    volatile gboolean thread;
    volatile gboolean ready;

    gint mode;
    gint freq;
    gint prevfreq;
    gint pi;
    gint pi_checked;
    gint rds_timer;
    gint pty;
    gint tp;
    gint ta;
    gint ms;
    gint ecc;
    gchar ps[9];
    guchar ps_err[8];
    gboolean ps_avail;
    gchar rt[2][65];
    gint filter;
    gint online;
    gboolean guest;
} tuner_t;

typedef struct pi
{
    guint16 pi;
    gboolean checked;
} pi_t;

tuner_t tuner;
extern gint filters[];
extern gint filters_bw[][FILTERS_N];

gpointer tuner_read(gpointer);
void tuner_parse(gchar, gchar[]);
void tuner_write(gchar*);
gboolean tuner_write_socket(int, gchar*, int);
void tuner_poweroff();
void tuner_modify_frequency(guint);
void tuner_modify_frequency_full(guint, guint, guint);
#endif
