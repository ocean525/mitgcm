C $Header: /u/gcmpack/MITgcm/pkg/rbcs/rbcs_ad_check_lev2_dir.h,v 1.5 2016/12/28 22:03:15 heimbach Exp $
C $Name:  $

CADJ STORE rbct0 = tapelev2, key = ilev_2
CADJ STORE rbct1 = tapelev2, key = ilev_2
CADJ STORE rbcs0 = tapelev2, key = ilev_2
CADJ STORE rbcs1 = tapelev2, key = ilev_2
CADJ STORE rbcsldrec = tapelev2, key = ilev_2

#ifndef DISABLE_RBCS_MOM
CADJ STORE rbcu0 = tapelev2, key = ilev_2
CADJ STORE rbcu1 = tapelev2, key = ilev_2
CADJ STORE rbcv0 = tapelev2, key = ilev_2
CADJ STORE rbcv1 = tapelev2, key = ilev_2
#endif

#ifdef ALLOW_PTRACERS
CADJ STORE rbcptr0 = tapelev2, key = ilev_2
CADJ STORE rbcptr1 = tapelev2, key = ilev_2
#endif
