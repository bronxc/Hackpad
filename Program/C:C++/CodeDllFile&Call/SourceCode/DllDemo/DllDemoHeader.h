#ifndef dllDemoHeader
#define dllDemoHeader

#ifdef DLLDEMO
#define EXPOETS_DEMO _declspec(dllexport)
#else
#define EXPORTS_DEMO _declspec(dllimport)
#endif

extern "C" EXPORTS_DEMO int add(int a, int b);

#endif