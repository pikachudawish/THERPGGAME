#ifndef SERVERAUXFUNCS_H
#define SERVERAUXFUNCS_H

#include "../../hdrs/hdrs_structs/structs_server.h"

int pkg_vrf_ui(int fd, package* pkg);
int pkg_get_adv(int fd, package* pkg);
int pkg_ins_ui(int fd, package* pkg);
int pkg_add_adv_to_user(int fd, package* pkg);
int pkg_ins(int fd, package* pkg);
int pkg_upd_adv(int fd, package* pkg);
int pkg_upd_s(int fd, package* pkg);
int pkg_upd_m(int fd, package* pkg);
int pkg_upd_e(int fd, package* pkg);
int pkg_upd_h(int fd, package* pkg);
int pkg_upd_c(int fd, package* pkg);
int pkg_upd_a(int fd, package* pkg);
int pkg_upd_b(int fd, package* pkg);
int pkg_upd_w(int fd, package* pkg);
int pkg_rmv(int fd, package* pkg);

#endif