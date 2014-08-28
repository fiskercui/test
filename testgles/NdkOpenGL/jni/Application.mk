APP_STL := gnustl_static
APP_ABI := armeabi-v7a
APP_PLATFORM :=android-14
NDK_TOOLCHAIN_VERSION=4.8


APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -DCOCOS2D_DEBUG=1 -fsigned-char
APP_LDFLAGS := -latomic
APP_OPTIM := debug
#APP_DEBUG := $(strip $(NDK_DEBUG))

#ifeq ($(APP_DEBUG),1)
#  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
#  APP_OPTIM := debug
#else
#  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
#  APP_OPTIM := release
#endif

#$(info $(APP_CPPFLAGS))
 # APP_CPPFLAGS += -DNDEBUG