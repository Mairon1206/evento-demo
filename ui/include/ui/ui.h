#ifdef WIN32
#ifdef evento_ui_EXPORTS
#define EVENTO_LIBRARY_API __declspec(dllexport)
#else
#define EVENTO_LIBRARY_API __declspec(dllimport)
#endif
#else
#define EVENTO_LIBRARY_API
#endif

EVENTO_LIBRARY_API void init_app();