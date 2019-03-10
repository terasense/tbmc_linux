#
# This file is the libmmio recipe.
#

SUMMARY = "Terasense memory mapped IO helper library"
SECTION = "PETALINUX/libs"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://libmmio.c \
	   file://mmio.h \
	   file://Makefile \
"

S = "${WORKDIR}"
PROVIDES = "libmmio"
TARGET_CC_ARCH += "${LDFLAGS}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${libdir}
	     oe_libinstall -so libmmio ${D}${libdir}
	     install -d -m 0655 ${D}${includedir}/libmmio
	     install -m 0644 ${S}/*.h ${D}${includedir}/libmmio/
}
