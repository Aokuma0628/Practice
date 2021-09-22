#include <stdio.h>

//オブジェクト指向ステートパターン
//複雑な条件分岐を柵上するために使用する

typedef struct STATE {
  const struct STATE *(* const stop)(const struct STATE *pThis);
  const struct STATE *(* const playOrPause)(const struct STATE *This);
} STATE;


static const STATE *g_pCurrentState;

static void initialize();
static void onStop();
static void onPlayOrPause();

static const STATE *ignore(const STATE *pThis);
static const STATE *startPlay(const STATE *pThis);
static const STATE *stopPlay(const STATE *pThis);
static const STATE *pausePlay(const STATE *pThis);
static const STATE *resumePlay(const STATE *pThis);

static const STATE g_idle = {
  ignore,
  startPlay
};

static const STATE g_play = {
  stopPlay,
  pausePlay
};

static const STATE g_pause = {
  stopPlay,
  resumePlay
};

//-------------------------------------
// private

static const STATE *ignore(const STATE *pThis)
{
  return g_pCurrentState;
}

static const STATE *startPlay(const STATE *pThis)
{
  return &g_idle;
}

static const STATE *stopPlay(const STATE *pThis)
{
  return &g_pause;
}

static const STATE *pausePlay(const STATE *pThis)
{
  return &g_play;
}

static const STATE *resumePlay(const STATE *pThis)
{
  return &g_play;
}

//-------------------------------------
// public

void initialize() {
  g_pCurrentState = &g_idle;
}

void onStop() {
  g_pCurrentState = g_pCurrentState->stop(g_pCurrentState);
}

void onPlayOrPause() {
  g_pCurrentState = g_pCurrentState->playOrPause(g_pCurrentState);
}



//==========================================================
// main

//============================================================