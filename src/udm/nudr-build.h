/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef UDM_NUDR_BUILD_H
#define UDM_NUDR_BUILD_H

#include "context.h"

#ifdef __cplusplus
extern "C" {
#endif

ogs_sbi_request_t *udm_nudr_dr_build_authentication_subscription(
        udm_ue_t *udm_ue, void *data);
ogs_sbi_request_t *udm_nudr_dr_build_query_subscription_provisioned(
        udm_ue_t *udm_ue, void *data);
ogs_sbi_request_t *udm_nudr_dr_build_update_authentication_status(
        udm_ue_t *udm_ue, void *data);
ogs_sbi_request_t *udm_nudr_dr_build_update_amf_context(
        udm_ue_t *udm_ue, void *data);
ogs_sbi_request_t *udm_nudr_dr_build_patch_amf_context(
        udm_ue_t *udm_ue, void *data);

ogs_sbi_request_t *udm_nudr_dr_build_update_smf_context(
        udm_sess_t *sess, void *data);
ogs_sbi_request_t *udm_nudr_dr_build_delete_smf_context(
        udm_sess_t *sess, void *data);

#ifdef __cplusplus
}
#endif

#endif /* UDM_NUDR_BUILD_H */
