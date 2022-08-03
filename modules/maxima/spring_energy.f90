SUBROUTINE & 
&mass_spring_1d_val(& 
&  val & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) val(1, 1) 
REAL(KIND=8) LR(1, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
val(1,1) = 5.0E-1*k(1,1)*(abs(LR(1,2)-LR(1,1))-l(1,1))**2
END 
SUBROUTINE & 
&mass_spring_1d_jac(& 
&  jac & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) jac(1, 2) 
REAL(KIND=8) LR(1, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
REAL(KIND=8)  tt1 
REAL(KIND=8)  tt2 
REAL(KIND=8)  tt3 
REAL(KIND=8)  tt4 
tt1 = LR(1,2)-LR(1,1)
tt2 = abs(tt1)
tt3 = 1/tt2
tt4 = tt2-l(1,1)
jac(1,1) = -1.0E+0*k(1,1)*tt1*tt3*tt4
jac(1,2) = 1.0E+0*k(1,1)*tt1*tt3*tt4
END 
SUBROUTINE & 
&mass_spring_1d_hes(& 
&  hes & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) hes(2, 2) 
REAL(KIND=8) LR(1, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
REAL(KIND=8)  tt1 
REAL(KIND=8)  tt2 
tt1 = 1.0E+0*k(1,1)
tt2 = -1.0E+0*k(1,1)
hes(1,1) = tt1
hes(1,2) = tt2
hes(2,1) = tt2
hes(2,2) = tt1
END 
SUBROUTINE & 
&mass_spring_2d_val(& 
&  val & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) val(1, 1) 
REAL(KIND=8) LR(2, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
val(1,1) = 5.0E-1*k(1,1)*(sqrt((LR(2,2)-LR(2,1))**2+(LR(1,2)-LR(1&
&,1))**2)-l(1,1))**2
END 
SUBROUTINE & 
&mass_spring_2d_jac(& 
&  jac & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) jac(1, 4) 
REAL(KIND=8) LR(2, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
REAL(KIND=8)  tt1 
REAL(KIND=8)  tt2 
REAL(KIND=8)  tt3 
REAL(KIND=8)  tt4 
REAL(KIND=8)  tt5 
tt1 = LR(1,2)-LR(1,1)
tt2 = LR(2,2)-LR(2,1)
tt3 = sqrt(tt2**2+tt1**2)
tt4 = 1/tt3
tt5 = tt3-l(1,1)
jac(1,1) = -1.0E+0*k(1,1)*tt1*tt4*tt5
jac(1,2) = -1.0E+0*k(1,1)*tt2*tt4*tt5
jac(1,3) = 1.0E+0*k(1,1)*tt1*tt4*tt5
jac(1,4) = 1.0E+0*k(1,1)*tt2*tt4*tt5
END 
SUBROUTINE & 
&mass_spring_2d_hes(& 
&  hes & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) hes(4, 4) 
REAL(KIND=8) LR(2, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
REAL(KIND=8)  tt1 
REAL(KIND=8)  tt2 
REAL(KIND=8)  tt3 
REAL(KIND=8)  tt4 
REAL(KIND=8)  tt5 
REAL(KIND=8)  tt6 
REAL(KIND=8)  tt7 
REAL(KIND=8)  tt8 
REAL(KIND=8)  tt9 
REAL(KIND=8)  tt10 
REAL(KIND=8)  tt11 
REAL(KIND=8)  tt12 
REAL(KIND=8)  tt13 
REAL(KIND=8)  tt14 
REAL(KIND=8)  tt15 
REAL(KIND=8)  tt16 
REAL(KIND=8)  tt17 
REAL(KIND=8)  tt18 
tt1 = LR(1,2)-LR(1,1)
tt2 = tt1**2
tt3 = LR(2,2)-LR(2,1)
tt4 = tt3**2
tt5 = tt4+tt2
tt6 = 1/tt5
tt7 = sqrt(tt5)
tt8 = 1/tt7**3
tt9 = tt7-l(1,1)
tt10 = 1/tt7
tt11 = 1.0E+0*k(1,1)*tt10*tt9
tt12 = tt11-1.0E+0*k(1,1)*tt2*tt8*tt9+1.0E+0*k(1,1)*tt2*tt6
tt13 = 1.0E+0*k(1,1)*tt1*tt3*tt6-1.0E+0*k(1,1)*tt1*tt3*tt8*tt9
tt14 = -1.0E+0*k(1,1)*tt10*tt9
tt15 = tt14+1.0E+0*k(1,1)*tt2*tt8*tt9-1.0E+0*k(1,1)*tt2*tt6
tt16 = 1.0E+0*k(1,1)*tt1*tt3*tt8*tt9-1.0E+0*k(1,1)*tt1*tt3*tt6
tt17 = tt11-1.0E+0*k(1,1)*tt4*tt8*tt9+1.0E+0*k(1,1)*tt4*tt6
tt18 = tt14+1.0E+0*k(1,1)*tt4*tt8*tt9-1.0E+0*k(1,1)*tt4*tt6
hes(1,1) = tt12
hes(1,2) = tt13
hes(1,3) = tt15
hes(1,4) = tt16
hes(2,1) = tt13
hes(2,2) = tt17
hes(2,3) = tt16
hes(2,4) = tt18
hes(3,1) = tt15
hes(3,2) = tt16
hes(3,3) = tt12
hes(3,4) = tt13
hes(4,1) = tt16
hes(4,2) = tt18
hes(4,3) = tt13
hes(4,4) = tt17
END 
SUBROUTINE & 
&mass_spring_3d_val(& 
&  val & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) val(1, 1) 
REAL(KIND=8) LR(3, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
val(1,1) = 5.0E-1*k(1,1)*(sqrt((LR(3,2)-LR(3,1))**2+(LR(2,2)-LR(2&
&,1))**2+(LR(1,2)-LR(1,1))**2)-l(1,1))**2
END 
SUBROUTINE & 
&mass_spring_3d_jac(& 
&  jac & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) jac(1, 6) 
REAL(KIND=8) LR(3, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
REAL(KIND=8)  tt1 
REAL(KIND=8)  tt2 
REAL(KIND=8)  tt3 
REAL(KIND=8)  tt4 
REAL(KIND=8)  tt5 
REAL(KIND=8)  tt6 
tt1 = LR(1,2)-LR(1,1)
tt2 = LR(2,2)-LR(2,1)
tt3 = LR(3,2)-LR(3,1)
tt4 = sqrt(tt3**2+tt2**2+tt1**2)
tt5 = 1/tt4
tt6 = tt4-l(1,1)
jac(1,1) = -1.0E+0*k(1,1)*tt1*tt5*tt6
jac(1,2) = -1.0E+0*k(1,1)*tt2*tt5*tt6
jac(1,3) = -1.0E+0*k(1,1)*tt3*tt5*tt6
jac(1,4) = 1.0E+0*k(1,1)*tt1*tt5*tt6
jac(1,5) = 1.0E+0*k(1,1)*tt2*tt5*tt6
jac(1,6) = 1.0E+0*k(1,1)*tt3*tt5*tt6
END 
SUBROUTINE & 
&mass_spring_3d_hes(& 
&  hes & 
&, LR & 
&, l & 
&, k & 
&) 
IMPLICIT NONE 
REAL(KIND=8) hes(6, 6) 
REAL(KIND=8) LR(3, 2) 
REAL(KIND=8) l(1, 1) 
REAL(KIND=8) k(1, 1) 
REAL(KIND=8)  tt1 
REAL(KIND=8)  tt2 
REAL(KIND=8)  tt3 
REAL(KIND=8)  tt4 
REAL(KIND=8)  tt5 
REAL(KIND=8)  tt6 
REAL(KIND=8)  tt7 
REAL(KIND=8)  tt8 
REAL(KIND=8)  tt9 
REAL(KIND=8)  tt10 
REAL(KIND=8)  tt11 
REAL(KIND=8)  tt12 
REAL(KIND=8)  tt13 
REAL(KIND=8)  tt14 
REAL(KIND=8)  tt15 
REAL(KIND=8)  tt16 
REAL(KIND=8)  tt17 
REAL(KIND=8)  tt18 
REAL(KIND=8)  tt19 
REAL(KIND=8)  tt20 
REAL(KIND=8)  tt21 
REAL(KIND=8)  tt22 
REAL(KIND=8)  tt23 
REAL(KIND=8)  tt24 
REAL(KIND=8)  tt25 
REAL(KIND=8)  tt26 
tt1 = LR(1,2)-LR(1,1)
tt2 = tt1**2
tt3 = LR(2,2)-LR(2,1)
tt4 = tt3**2
tt5 = LR(3,2)-LR(3,1)
tt6 = tt5**2
tt7 = tt6+tt4+tt2
tt8 = 1/tt7
tt9 = sqrt(tt7)
tt10 = 1/tt9**3
tt11 = tt9-l(1,1)
tt12 = 1/tt9
tt13 = 1.0E+0*k(1,1)*tt12*tt11
tt14 = tt13-1.0E+0*k(1,1)*tt2*tt10*tt11+1.0E+0*k(1,1)*tt2*tt8
tt15 = 1.0E+0*k(1,1)*tt1*tt3*tt8-1.0E+0*k(1,1)*tt1*tt3*tt10*tt11
tt16 = 1.0E+0*k(1,1)*tt1*tt5*tt8-1.0E+0*k(1,1)*tt1*tt5*tt10*tt11
tt17 = -1.0E+0*k(1,1)*tt12*tt11
tt18 = tt17+1.0E+0*k(1,1)*tt2*tt10*tt11-1.0E+0*k(1,1)*tt2*tt8
tt19 = 1.0E+0*k(1,1)*tt1*tt3*tt10*tt11-1.0E+0*k(1,1)*tt1*tt3*tt8
tt20 = 1.0E+0*k(1,1)*tt1*tt5*tt10*tt11-1.0E+0*k(1,1)*tt1*tt5*tt8
tt21 = tt13-1.0E+0*k(1,1)*tt4*tt10*tt11+1.0E+0*k(1,1)*tt4*tt8
tt22 = 1.0E+0*k(1,1)*tt3*tt5*tt8-1.0E+0*k(1,1)*tt3*tt5*tt10*tt11
tt23 = tt17+1.0E+0*k(1,1)*tt4*tt10*tt11-1.0E+0*k(1,1)*tt4*tt8
tt24 = 1.0E+0*k(1,1)*tt3*tt5*tt10*tt11-1.0E+0*k(1,1)*tt3*tt5*tt8
tt25 = tt13-1.0E+0*k(1,1)*tt6*tt10*tt11+1.0E+0*k(1,1)*tt6*tt8
tt26 = tt17+1.0E+0*k(1,1)*tt6*tt10*tt11-1.0E+0*k(1,1)*tt6*tt8
hes(1,1) = tt14
hes(1,2) = tt15
hes(1,3) = tt16
hes(1,4) = tt18
hes(1,5) = tt19
hes(1,6) = tt20
hes(2,1) = tt15
hes(2,2) = tt21
hes(2,3) = tt22
hes(2,4) = tt19
hes(2,5) = tt23
hes(2,6) = tt24
hes(3,1) = tt16
hes(3,2) = tt22
hes(3,3) = tt25
hes(3,4) = tt20
hes(3,5) = tt24
hes(3,6) = tt26
hes(4,1) = tt18
hes(4,2) = tt19
hes(4,3) = tt20
hes(4,4) = tt14
hes(4,5) = tt15
hes(4,6) = tt16
hes(5,1) = tt19
hes(5,2) = tt23
hes(5,3) = tt24
hes(5,4) = tt15
hes(5,5) = tt21
hes(5,6) = tt22
hes(6,1) = tt20
hes(6,2) = tt24
hes(6,3) = tt26
hes(6,4) = tt16
hes(6,5) = tt22
hes(6,6) = tt25
END 
