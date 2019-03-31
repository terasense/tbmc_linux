#
# This file is the tsapi recipe.
#

SUMMARY = "Terasense API suite"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

INSANE_SKIP_${PN} += "file-rdeps"

SRC_URI = "file://tbmc_api \
	"

S = "${WORKDIR}"

do_install() {
	     install -d ${D}/${libexecdir}
	     cp -R ${S}/tbmc_api ${D}/${libexecdir}
}
