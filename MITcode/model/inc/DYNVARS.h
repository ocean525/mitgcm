C $Header: /u/gcmpack/MITgcm/model/inc/DYNVARS.h,v 1.50 2016/11/28 22:55:00 jmc Exp $
C $Name:  $

CBOP
C     !ROUTINE: DYNVARS.h
C     !INTERFACE:
C     include "DYNVARS.h"
C     !DESCRIPTION:
C     \bv
C     *==========================================================*
C     | DYNVARS.h
C     | o Dynamical model variables (common block DYNVARS_R)  动态模型变量  公共块  DYNVARS_R
C     *==========================================================*
C     | The value and two levels of time tendency are held for 每个预测变量的值以及俩级时间趋势
C     | each prognostic variable.
C     *==========================================================*
C     \ev
CEOP

C     State Variables:   状态变量
C     etaN  :: free-surface r-anomaly (r unit) at current time level     当前时间水平的自由面r异常（r单位）
C     uVel  :: zonal velocity (m/s, i=1 held at western face)          纬向速度（m/s，在西面保持i=1）
C     vVel  :: meridional velocity (m/s, j=1 held at southern face)    经向速度（m/s，j=1，保持在南面）
C     theta :: potential temperature (oC, held at pressure/tracer point) 潜在温度（oC，保持在压力/示踪点）
C     salt  :: salinity (ppt, held at pressure/tracer point)  盐度（ppt，保持在压力/示踪点）
C     gX, gxNm1 :: Time tendencies at current and previous time levels.  当前和以前时间水平的时间趋势。
C     etaH  :: surface r-anomaly, advanced in time consistently 地表r异常，在时间上与2.D气流发散一致（精确守恒）：
C              with 2.D flow divergence (Exact-Conservation):
C                etaH^n+1 = etaH^n - delta_t*Div.(H^n U^n+1)
C  note: a) used with "exactConserv", necessary for Non-Lin free-surf and mixed  与“ExactConserve”一起使用，用于非Lin自由冲浪和混合向前/向后自由冲浪时间步进（例如Crank Nickelson）
C           forward/backward free-surf time stepping (e.g., Crank-Nickelson)
C        b) same as etaN but not necessarily at the same time, e.g.: 与etaN相同但不一定同时存在，例如：implicDiv2DFlow=1=>etaH=etaN=0=>etaH=etaN^（n-1）；
C           implicDiv2DFlow=1 => etaH=etaN ; =0 => etaH=etaN^(n-1);

#ifdef ALLOW_ADAMSBASHFORTH_3           这是在CPP_OPTIONS.h等里边定义的内容
      COMMON /DYNVARS_R/
     &                   etaN,
     &                   uVel,vVel,wVel,theta,salt,
     &                   gU,   gV,
     &                   guNm, gvNm, gtNm, gsNm
#else /* ALLOW_ADAMSBASHFORTH_3 */
      COMMON /DYNVARS_R/
     &                   etaN,
     &                   uVel,vVel,wVel,theta,salt,
     &                   gU,   gV,
     &                   guNm1,gvNm1,gtNm1,gsNm1
#endif /* ALLOW_ADAMSBASHFORTH_3 */
      _RL  etaN  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      _RL  uVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  vVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  wVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  theta(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  salt (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  gU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  gV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
#ifdef ALLOW_ADAMSBASHFORTH_3
      _RL  guNm(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy,2)
      _RL  gvNm(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy,2)
      _RL  gtNm(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy,2)
      _RL  gsNm(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy,2)
#else /* ALLOW_ADAMSBASHFORTH_3 */
      _RL  guNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  gvNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  gtNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  gsNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
#endif /* ALLOW_ADAMSBASHFORTH_3 */

#ifdef USE_OLD_EXTERNAL_FORCING
      COMMON /DYNVARS_OLD/
     &                   gT,   gS
      _RL  gT(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  gS(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
#endif

      COMMON /DYNVARS_R_2/
     &                   etaH
      _RL  etaH  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)

#if (defined (ALLOW_3D_DIFFKR) || defined (ALLOW_DIFFKR_CONTROL))
C     diffKr :: full 3D specification of Laplacian diffusion coeff.
C               for mixing of tracers vertically ( units of r^2/s )
      COMMON /DYNVARS_DIFFKR/
     &                       diffKr
      _RL  diffKr (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
#endif

C   The following blocks containing requires anomaly fields of control vars
C   and related to Options:
C   ALLOW_KAPGM_CONTROL , ALLOW_KAPREDI_CONTROL and ALLOW_BOTTOMDRAG_CONTROL
C   have been moved to header file "CTRL_FIELDS.h"

#ifdef ALLOW_BL79_LAT_VARY
C     BL79LatArray :: is used for latitudinal dependence of
C                     BryanLewis79 vertical diffusivity
      COMMON /DYNVARS_BL79LatArray/ BL79LatArray
      _RL BL79LatArray (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
#endif

C     Diagnostic Variables:
C     phiHydLow    :: Phi-Hydrostatic at r-lower boundary
C                     (bottom in z-coordinates, top in p-coordinates)
C     totPhiHyd    :: total hydrostatic Potential (anomaly, for now),
C                     at cell center level ; includes surface contribution.
C                     (for diagnostic + used in Z-coord with EOS_funct_P)
C     rhoInSitu    :: In-Situ density anomaly [kg/m^3] at cell center level.
C     hMixLayer    :: Mixed layer depth [m]
C                     (for diagnostic + used GMRedi "fm07")
C     IVDConvCount :: Impl.Vert.Diffusion convection counter:
C                     = 0 (not convecting) or 1 (convecting)
      COMMON /DYNVARS_DIAG/
     &                phiHydLow, totPhiHyd,
     &                rhoInSitu,
     &                hMixLayer, IVDConvCount
      _RL  phiHydLow(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      _RL  totPhiHyd(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  rhoInSitu(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  hMixLayer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      _RL  IVDConvCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)

#ifdef ALLOW_SOLVE4_PS_AND_DRAG
C     Variables for Implicit friction (& vert. visc) in 2-D pressure solver
C     dU_psFacX    :: zonal velocity increment factor from (implicit) surf.
C                     pressure gradient in X (no Units)
C     dV_psFacY    :: merid velocity increment factor from (implicit) surf.
C                     pressure gradient in Y (no Units)

      COMMON /DYNVARS_DRAG_IN_PS/
     &                dU_psFacX, dV_psFacY
      _RL  dU_psFacX(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      _RL  dV_psFacY(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
#endif /* ALLOW_SOLVE4_PS_AND_DRAG */
