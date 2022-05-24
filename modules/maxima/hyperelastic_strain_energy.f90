SUBROUTINE &
&linear_elas_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
tt1 = 1.0E+0*F(1,1)
tt2 = 1.0E+0*F(2,2)
val(1,1) = 5.0E-1*lam(1,1)*(tt2+tt1-2)**2+mu(1,1)*((tt2-1)**2+5.0&
&E-1*(F(2,1)+F(1,2))**2+(tt1-1)**2)
END
SUBROUTINE &
&linear_elas_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = 1.0E+0*F(1,1)
tt2 = 1.0E+0*F(2,2)
tt3 = 1.0E+0*lam(1,1)*(tt2+tt1-2)
tt4 = 1.0E+0*mu(1,1)*(F(2,1)+F(1,2))
jac(1,1) = tt3+2.0E+0*(tt1-1)*mu(1,1)
jac(1,2) = tt4
jac(1,3) = tt4
jac(1,4) = tt3+2.0E+0*mu(1,1)*(tt2-1)
END
SUBROUTINE &
&linear_elas_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = 1.0E+0*lam(1,1)
tt2 = 2.0E+0*mu(1,1)+tt1
tt3 = 1.0E+0*mu(1,1)
hes(1,1) = tt2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = tt1
hes(2,1) = 0
hes(2,2) = tt3
hes(2,3) = tt3
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = tt3
hes(3,3) = tt3
hes(3,4) = 0
hes(4,1) = tt1
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = tt2
END
SUBROUTINE &
&stvk_elas_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
tt1 = F(2,1)**2+F(1,1)**2-1
tt2 = F(2,2)**2+F(1,2)**2-1
val(1,1) = 5.0E-1*lam(1,1)*(5.0E-1*tt2+5.0E-1*tt1)**2+mu(1,1)*(2.&
&5E-1*tt2**2+5.0E-1*(F(2,1)*F(2,2)+F(1,1)*F(1,2))**2+2.5E-1*tt1**2&
&)
END
SUBROUTINE &
&stvk_elas_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = F(2,1)**2+F(1,1)**2-1
tt2 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(2,2)**2+F(1,2)**2-1
tt4 = 5.0E-1*tt3+5.0E-1*tt1
jac(1,1) = 1.0E+0*F(1,1)*lam(1,1)*tt4+mu(1,1)*(1.0E+0*F(1,2)*tt2+&
&1.0E+0*F(1,1)*tt1)
jac(1,2) = 1.0E+0*lam(1,1)*F(2,1)*tt4+mu(1,1)*(1.0E+0*F(2,2)*tt2+&
&1.0E+0*F(2,1)*tt1)
jac(1,3) = mu(1,1)*(1.0E+0*F(1,2)*tt3+1.0E+0*F(1,1)*tt2)+1.0E+0*l&
&am(1,1)*F(1,2)*tt4
jac(1,4) = mu(1,1)*(1.0E+0*F(2,2)*tt3+1.0E+0*F(2,1)*tt2)+1.0E+0*l&
&am(1,1)*F(2,2)*tt4
END
SUBROUTINE &
&stvk_elas_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = F(2,1)**2
tt4 = tt3+tt1-1
tt5 = 1.0E+0*tt4
tt6 = F(2,2)**2
tt7 = tt6+tt2-1
tt8 = 1.0E+0*lam(1,1)*(5.0E-1*tt7+5.0E-1*tt4)
tt9 = mu(1,1)*(1.0E+0*F(1,2)*F(2,2)+2.0E+0*F(1,1)*F(2,1))+1.0E+0*&
&F(1,1)*lam(1,1)*F(2,1)
tt10 = 1.0E+0*(F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt11 = mu(1,1)*(tt10+1.0E+0*F(1,1)*F(1,2))+1.0E+0*F(1,1)*lam(1,1)&
&*F(1,2)
tt12 = 1.0E+0*F(1,1)*lam(1,1)*F(2,2)+1.0E+0*mu(1,1)*F(1,2)*F(2,1)&
&
tt13 = 1.0E+0*F(1,1)*mu(1,1)*F(2,2)+1.0E+0*lam(1,1)*F(1,2)*F(2,1)&
&
tt14 = mu(1,1)*(tt10+1.0E+0*F(2,1)*F(2,2))+1.0E+0*lam(1,1)*F(2,1)&
&*F(2,2)
tt15 = 1.0E+0*tt7
tt16 = mu(1,1)*(2.0E+0*F(1,2)*F(2,2)+1.0E+0*F(1,1)*F(2,1))+1.0E+0&
&*lam(1,1)*F(1,2)*F(2,2)
hes(1,1) = tt8+mu(1,1)*(tt5+1.0E+0*tt2+2.0E+0*tt1)+1.0E+0*tt1*lam&
&(1,1)
hes(1,2) = tt9
hes(1,3) = tt11
hes(1,4) = tt12
hes(2,1) = tt9
hes(2,2) = tt8+mu(1,1)*(1.0E+0*tt6+tt5+2.0E+0*tt3)+1.0E+0*lam(1,1&
&)*tt3
hes(2,3) = tt13
hes(2,4) = tt14
hes(3,1) = tt11
hes(3,2) = tt13
hes(3,3) = mu(1,1)*(tt15+2.0E+0*tt2+1.0E+0*tt1)+tt8+1.0E+0*lam(1,&
&1)*tt2
hes(3,4) = tt16
hes(4,1) = tt12
hes(4,2) = tt14
hes(4,3) = tt16
hes(4,4) = mu(1,1)*(tt15+2.0E+0*tt6+1.0E+0*tt3)+tt8+1.0E+0*lam(1,&
&1)*tt6
END
SUBROUTINE &
&coro_elas_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
val(1,1) = 5.0E-1*lam(1,1)*(5.0E-1*(2*F(2,2)*R(2,2)+2*F(1,2)*R(1,&
&2))+5.0E-1*(2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-2)**2+mu(1,1)*((1.0E&
&+0*F(2,2)*R(2,2)+1.0E+0*F(1,2)*R(1,2)-1)**2+5.0E-1*(F(2,1)*R(2,2)&
&+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2))**2+(1.0E+0*F(2,1)*R(2&
&,1)+1.0E+0*F(1,1)*R(1,1)-1)**2)
END
SUBROUTINE &
&coro_elas_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = 1.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1,1)-1
tt2 = F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = 5.0E-1*(2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))+5.0E-1*(2*F(2,1)*R&
&(2,1)+2*F(1,1)*R(1,1))-2
tt4 = 1.0E+0*F(2,2)*R(2,2)+1.0E+0*F(1,2)*R(1,2)-1
jac(1,1) = 1.0E+0*R(1,1)*lam(1,1)*tt3+mu(1,1)*(1.0E+0*R(1,2)*tt2+&
&2.0E+0*R(1,1)*tt1)
jac(1,2) = 1.0E+0*lam(1,1)*R(2,1)*tt3+mu(1,1)*(1.0E+0*R(2,2)*tt2+&
&2.0E+0*R(2,1)*tt1)
jac(1,3) = 1.0E+0*lam(1,1)*R(1,2)*tt3+mu(1,1)*(2.0E+0*R(1,2)*tt4+&
&1.0E+0*R(1,1)*tt2)
jac(1,4) = 1.0E+0*lam(1,1)*R(2,2)*tt3+mu(1,1)*(2.0E+0*R(2,2)*tt4+&
&1.0E+0*R(2,1)*tt2)
END
SUBROUTINE &
&coro_elas_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
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
tt1 = R(1,1)**2
tt2 = R(1,2)**2
tt3 = mu(1,1)*(1.0E+0*R(1,2)*R(2,2)+2.0E+0*R(1,1)*R(2,1))+1.0E+0*&
&R(1,1)*lam(1,1)*R(2,1)
tt4 = 1.0E+0*R(1,1)*mu(1,1)*R(1,2)+1.0E+0*R(1,1)*lam(1,1)*R(1,2)
tt5 = 1.0E+0*R(1,1)*lam(1,1)*R(2,2)+1.0E+0*mu(1,1)*R(1,2)*R(2,1)
tt6 = R(2,1)**2
tt7 = R(2,2)**2
tt8 = 1.0E+0*R(1,1)*mu(1,1)*R(2,2)+1.0E+0*lam(1,1)*R(1,2)*R(2,1)
tt9 = 1.0E+0*mu(1,1)*R(2,1)*R(2,2)+1.0E+0*lam(1,1)*R(2,1)*R(2,2)
tt10 = mu(1,1)*(2.0E+0*R(1,2)*R(2,2)+1.0E+0*R(1,1)*R(2,1))+1.0E+0&
&*lam(1,1)*R(1,2)*R(2,2)
hes(1,1) = mu(1,1)*(1.0E+0*tt2+2.0E+0*tt1)+1.0E+0*tt1*lam(1,1)
hes(1,2) = tt3
hes(1,3) = tt4
hes(1,4) = tt5
hes(2,1) = tt3
hes(2,2) = mu(1,1)*(1.0E+0*tt7+2.0E+0*tt6)+1.0E+0*lam(1,1)*tt6
hes(2,3) = tt8
hes(2,4) = tt9
hes(3,1) = tt4
hes(3,2) = tt8
hes(3,3) = mu(1,1)*(2.0E+0*tt2+1.0E+0*tt1)+1.0E+0*lam(1,1)*tt2
hes(3,4) = tt10
hes(4,1) = tt5
hes(4,2) = tt9
hes(4,3) = tt10
hes(4,4) = mu(1,1)*(2.0E+0*tt7+1.0E+0*tt6)+1.0E+0*lam(1,1)*tt7
END
SUBROUTINE &
&mcadams_coro_elas_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
val(1,1) = mu(1,1)*((R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))**2+(R(1,2)&
&-F(1,2))**2+(R(1,1)-F(1,1))**2)+5.0E-1*lam(1,1)*((-R(2,2))+F(2,2)&
&-R(1,1)+F(1,1))**2
END
SUBROUTINE &
&mcadams_coro_elas_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*lam(1,1)*((-R(2,2))+F(2,2)-R(1,1)+F(1,1))
jac(1,1) = tt1-2*(R(1,1)-F(1,1))*mu(1,1)
jac(1,2) = -2*mu(1,1)*(R(2,1)-F(2,1))
jac(1,3) = -2*mu(1,1)*(R(1,2)-F(1,2))
jac(1,4) = tt1-2*mu(1,1)*(R(2,2)-F(2,2))
END
SUBROUTINE &
&mcadams_coro_elas_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 1.0E+0*lam(1,1)
tt2 = 2*mu(1,1)
tt3 = tt2+tt1
hes(1,1) = tt3
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = tt1
hes(2,1) = 0
hes(2,2) = tt2
hes(2,3) = 0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = tt2
hes(3,4) = 0
hes(4,1) = tt1
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = tt3
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
val(1,1) = mu(1,1)*((R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))**2+(R(1,2)&
&-F(1,2))**2+(R(1,1)-F(1,1))**2)+5.0E-1*lam(1,1)*(F(1,1)*F(2,2)-F(&
&1,2)*F(2,1)-1)**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*lam(1,1)*F(2,2)*tt1-2*(R(1,1)-F(1,1))*mu(1,1)
jac(1,2) = (-1.0E+0*lam(1,1)*F(1,2)*tt1)-2*mu(1,1)*(R(2,1)-F(2,1)&
&)
jac(1,3) = (-1.0E+0*lam(1,1)*F(2,1)*tt1)-2*mu(1,1)*(R(1,2)-F(1,2)&
&)
jac(1,4) = 1.0E+0*F(1,1)*lam(1,1)*tt1-2*mu(1,1)*(R(2,2)-F(2,2))
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
REAL(KIND=8)  tt8
tt1 = 2*mu(1,1)
tt2 = -1.0E+0*lam(1,1)*F(1,2)*F(2,2)
tt3 = -1.0E+0*lam(1,1)*F(2,1)*F(2,2)
tt4 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt5 = 1.0E+0*lam(1,1)*tt4+1.0E+0*F(1,1)*lam(1,1)*F(2,2)
tt6 = 1.0E+0*lam(1,1)*F(1,2)*F(2,1)-1.0E+0*lam(1,1)*tt4
tt7 = -1.0E+0*F(1,1)*lam(1,1)*F(1,2)
tt8 = -1.0E+0*F(1,1)*lam(1,1)*F(2,1)
hes(1,1) = 1.0E+0*lam(1,1)*F(2,2)**2+tt1
hes(1,2) = tt2
hes(1,3) = tt3
hes(1,4) = tt5
hes(2,1) = tt2
hes(2,2) = 1.0E+0*lam(1,1)*F(1,2)**2+tt1
hes(2,3) = tt6
hes(2,4) = tt7
hes(3,1) = tt3
hes(3,2) = tt6
hes(3,3) = 1.0E+0*lam(1,1)*F(2,1)**2+tt1
hes(3,4) = tt8
hes(4,1) = tt5
hes(4,2) = tt7
hes(4,3) = tt8
hes(4,4) = tt1+1.0E+0*F(1,1)**2*lam(1,1)
END
SUBROUTINE &
&bonet08_neohookean_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
tt1 = log(F(1,1)*F(2,2)-F(1,2)*F(2,1))
val(1,1) = 5.0E-1*lam(1,1)*tt1**2-mu(1,1)*tt1+5.0E-1*mu(1,1)*(F(2&
&,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2-3)
END
SUBROUTINE &
&bonet08_neohookean_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt2 = 1/tt1
tt3 = log(tt1)
jac(1,1) = 1.0E+0*lam(1,1)*F(2,2)*tt2*tt3-mu(1,1)*F(2,2)*tt2+1.0E&
&+0*F(1,1)*mu(1,1)
jac(1,2) = (-1.0E+0*lam(1,1)*F(1,2)*tt2*tt3)+mu(1,1)*F(1,2)*tt2+1&
&.0E+0*mu(1,1)*F(2,1)
jac(1,3) = (-1.0E+0*lam(1,1)*F(2,1)*tt2*tt3)+mu(1,1)*F(2,1)*tt2+1&
&.0E+0*mu(1,1)*F(1,2)
jac(1,4) = 1.0E+0*F(1,1)*lam(1,1)*tt2*tt3-F(1,1)*mu(1,1)*tt2+1.0E&
&+0*mu(1,1)*F(2,2)
END
SUBROUTINE &
&bonet08_neohookean_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = 1.0E+0*mu(1,1)
tt2 = F(2,2)**2
tt3 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt4 = 1/tt3**2
tt5 = log(tt3)
tt6 = 1.0E+0*lam(1,1)*F(1,2)*F(2,2)*tt4*tt5-mu(1,1)*F(1,2)*F(2,2)&
&*tt4-1.0E+0*lam(1,1)*F(1,2)*F(2,2)*tt4
tt7 = 1.0E+0*lam(1,1)*F(2,1)*F(2,2)*tt4*tt5-mu(1,1)*F(2,1)*F(2,2)&
&*tt4-1.0E+0*lam(1,1)*F(2,1)*F(2,2)*tt4
tt8 = 1/tt3
tt9 = 1.0E+0*lam(1,1)*tt8*tt5-1.0E+0*F(1,1)*lam(1,1)*F(2,2)*tt4*t&
&t5-mu(1,1)*tt8+F(1,1)*mu(1,1)*F(2,2)*tt4+1.0E+0*F(1,1)*lam(1,1)*F&
&(2,2)*tt4
tt10 = F(1,2)**2
tt11 = (-1.0E+0*lam(1,1)*tt8*tt5)-1.0E+0*lam(1,1)*F(1,2)*F(2,1)*t&
&t4*tt5+mu(1,1)*tt8+mu(1,1)*F(1,2)*F(2,1)*tt4+1.0E+0*lam(1,1)*F(1,&
&2)*F(2,1)*tt4
tt12 = 1.0E+0*F(1,1)*lam(1,1)*F(1,2)*tt4*tt5-F(1,1)*mu(1,1)*F(1,2&
&)*tt4-1.0E+0*F(1,1)*lam(1,1)*F(1,2)*tt4
tt13 = F(2,1)**2
tt14 = 1.0E+0*F(1,1)*lam(1,1)*F(2,1)*tt4*tt5-F(1,1)*mu(1,1)*F(2,1&
&)*tt4-1.0E+0*F(1,1)*lam(1,1)*F(2,1)*tt4
tt15 = F(1,1)**2
hes(1,1) = (-1.0E+0*lam(1,1)*tt2*tt4*tt5)+mu(1,1)*tt2*tt4+1.0E+0*&
&lam(1,1)*tt2*tt4+tt1
hes(1,2) = tt6
hes(1,3) = tt7
hes(1,4) = tt9
hes(2,1) = tt6
hes(2,2) = (-1.0E+0*lam(1,1)*tt10*tt4*tt5)+mu(1,1)*tt10*tt4+1.0E+&
&0*lam(1,1)*tt10*tt4+tt1
hes(2,3) = tt11
hes(2,4) = tt12
hes(3,1) = tt7
hes(3,2) = tt11
hes(3,3) = (-1.0E+0*lam(1,1)*tt13*tt4*tt5)+mu(1,1)*tt13*tt4+1.0E+&
&0*lam(1,1)*tt13*tt4+tt1
hes(3,4) = tt14
hes(4,1) = tt9
hes(4,2) = tt12
hes(4,3) = tt14
hes(4,4) = (-1.0E+0*tt15*lam(1,1)*tt4*tt5)+tt15*mu(1,1)*tt4+1.0E+&
&0*tt15*lam(1,1)*tt4+tt1
END
SUBROUTINE &
&ogden97_neohookean_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
tt1 = -F(1,2)*F(2,1)
tt2 = F(1,1)*F(2,2)
val(1,1) = (-mu(1,1)*log(tt2+tt1))+5.0E-1*lam(1,1)*(tt2+tt1-1)**2&
&+5.0E-1*mu(1,1)*(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2-3)
END
SUBROUTINE &
&ogden97_neohookean_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = -F(1,2)*F(2,1)
tt2 = F(1,1)*F(2,2)
tt3 = tt2+tt1-1
tt4 = 1/(tt2+tt1)
jac(1,1) = (-mu(1,1)*F(2,2)*tt4)+1.0E+0*lam(1,1)*F(2,2)*tt3+1.0E+&
&0*F(1,1)*mu(1,1)
jac(1,2) = mu(1,1)*F(1,2)*tt4-1.0E+0*lam(1,1)*F(1,2)*tt3+1.0E+0*m&
&u(1,1)*F(2,1)
jac(1,3) = mu(1,1)*F(2,1)*tt4-1.0E+0*lam(1,1)*F(2,1)*tt3+1.0E+0*m&
&u(1,1)*F(1,2)
jac(1,4) = (-F(1,1)*mu(1,1)*tt4)+1.0E+0*F(1,1)*lam(1,1)*tt3+1.0E+&
&0*mu(1,1)*F(2,2)
END
SUBROUTINE &
&ogden97_neohookean_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = 1.0E+0*mu(1,1)
tt2 = F(2,2)**2
tt3 = -F(1,2)*F(2,1)
tt4 = F(1,1)*F(2,2)
tt5 = tt4+tt3
tt6 = 1/tt5**2
tt7 = (-mu(1,1)*F(1,2)*F(2,2)*tt6)-1.0E+0*lam(1,1)*F(1,2)*F(2,2)
tt8 = (-mu(1,1)*F(2,1)*F(2,2)*tt6)-1.0E+0*lam(1,1)*F(2,1)*F(2,2)
tt9 = tt4+tt3-1
tt10 = 1/tt5
tt11 = (-mu(1,1)*tt10)+F(1,1)*mu(1,1)*F(2,2)*tt6+1.0E+0*lam(1,1)*&
&tt9+1.0E+0*F(1,1)*lam(1,1)*F(2,2)
tt12 = F(1,2)**2
tt13 = mu(1,1)*tt10+mu(1,1)*F(1,2)*F(2,1)*tt6-1.0E+0*lam(1,1)*tt9&
&+1.0E+0*lam(1,1)*F(1,2)*F(2,1)
tt14 = (-F(1,1)*mu(1,1)*F(1,2)*tt6)-1.0E+0*F(1,1)*lam(1,1)*F(1,2)&
&
tt15 = F(2,1)**2
tt16 = (-F(1,1)*mu(1,1)*F(2,1)*tt6)-1.0E+0*F(1,1)*lam(1,1)*F(2,1)&
&
tt17 = F(1,1)**2
hes(1,1) = mu(1,1)*tt2*tt6+1.0E+0*lam(1,1)*tt2+tt1
hes(1,2) = tt7
hes(1,3) = tt8
hes(1,4) = tt11
hes(2,1) = tt7
hes(2,2) = mu(1,1)*tt12*tt6+1.0E+0*lam(1,1)*tt12+tt1
hes(2,3) = tt13
hes(2,4) = tt14
hes(3,1) = tt8
hes(3,2) = tt13
hes(3,3) = mu(1,1)*tt15*tt6+1.0E+0*lam(1,1)*tt15+tt1
hes(3,4) = tt16
hes(4,1) = tt11
hes(4,2) = tt14
hes(4,3) = tt16
hes(4,4) = tt17*mu(1,1)*tt6+tt1+1.0E+0*tt17*lam(1,1)
END
SUBROUTINE &
&bower09_neohookean_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
tt1 = -F(1,2)*F(2,1)
tt2 = F(1,1)*F(2,2)
val(1,1) = 5.0E-1*lam(1,1)*(tt2+tt1-1)**2+5.0E-1*mu(1,1)*((F(2,2)&
&**2+F(2,1)**2+F(1,2)**2+F(1,1)**2)/(tt2+tt1)**(2.0E+0/3.0E+0)-3)
END
SUBROUTINE &
&bower09_neohookean_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = -F(1,2)*F(2,1)
tt2 = F(1,1)*F(2,2)
tt3 = tt2+tt1-1
tt4 = tt2+tt1
tt5 = tt4**((-5.0E+0)/3.0E+0)
tt6 = F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2
tt7 = tt4**((-2.0E+0)/3.0E+0)
jac(1,1) = 5.0E-1*mu(1,1)*(2*F(1,1)*tt7+((-2.0E+0)*F(2,2)*tt5*tt6&
&)/3.0E+0)+1.0E+0*lam(1,1)*F(2,2)*tt3
jac(1,2) = 5.0E-1*mu(1,1)*(2*F(2,1)*tt7+(2.0E+0*F(1,2)*tt5*tt6)/3&
&.0E+0)-1.0E+0*lam(1,1)*F(1,2)*tt3
jac(1,3) = 5.0E-1*mu(1,1)*(2*F(1,2)*tt7+(2.0E+0*F(2,1)*tt5*tt6)/3&
&.0E+0)-1.0E+0*lam(1,1)*F(2,1)*tt3
jac(1,4) = 5.0E-1*mu(1,1)*(2*F(2,2)*tt7+((-2.0E+0)*F(1,1)*tt5*tt6&
&)/3.0E+0)+1.0E+0*F(1,1)*lam(1,1)*tt3
END
SUBROUTINE &
&bower09_neohookean_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(2,2)**2
tt2 = -F(1,2)*F(2,1)
tt3 = F(1,1)*F(2,2)
tt4 = tt3+tt2
tt5 = tt4**((-8.0E+0)/3.0E+0)
tt6 = F(1,1)**2
tt7 = F(1,2)**2
tt8 = F(2,1)**2
tt9 = tt1+tt8+tt7+tt6
tt10 = tt4**((-5.0E+0)/3.0E+0)
tt11 = ((-8.0E+0)*F(1,1)*F(2,2)*tt10)/3.0E+0
tt12 = 2/tt4**(2.0E+0/3.0E+0)
tt13 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,1)*F(2,2)*tt10)/3.0E+0+(4.0&
&E+0*F(1,1)*F(1,2)*tt10)/3.0E+0+((-1.0E+1)*F(1,2)*F(2,2)*tt5*tt9)/&
&9.0E+0)-1.0E+0*lam(1,1)*F(1,2)*F(2,2)
tt14 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(1,2)*F(2,2)*tt10)/3.0E+0+(4.0&
&E+0*F(1,1)*F(2,1)*tt10)/3.0E+0+((-1.0E+1)*F(2,1)*F(2,2)*tt5*tt9)/&
&9.0E+0)-1.0E+0*lam(1,1)*F(2,1)*F(2,2)
tt15 = tt3+tt2-1
tt16 = 5.0E-1*mu(1,1)*(((-4.0E+0)*tt1*tt10)/3.0E+0+((-4.0E+0)*tt6&
&*tt10)/3.0E+0+((-2.0E+0)*tt10*tt9)/3.0E+0+(1.0E+1*F(1,1)*F(2,2)*t&
&t5*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt15+1.0E+0*F(1,1)*lam(1,1)*F(2,2&
&)
tt17 = (8.0E+0*F(1,2)*F(2,1)*tt10)/3.0E+0
tt18 = 5.0E-1*mu(1,1)*((4.0E+0*tt8*tt10)/3.0E+0+(4.0E+0*tt7*tt10)&
&/3.0E+0+(2.0E+0*tt10*tt9)/3.0E+0+(1.0E+1*F(1,2)*F(2,1)*tt5*tt9)/9&
&.0E+0)-1.0E+0*lam(1,1)*tt15+1.0E+0*lam(1,1)*F(1,2)*F(2,1)
tt19 = 5.0E-1*mu(1,1)*((4.0E+0*F(1,2)*F(2,2)*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*F(2,1)*tt10)/3.0E+0+((-1.0E+1)*F(1,1)*F(1,2)*tt5*tt9)/&
&9.0E+0)-1.0E+0*F(1,1)*lam(1,1)*F(1,2)
tt20 = 5.0E-1*mu(1,1)*((4.0E+0*F(2,1)*F(2,2)*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*F(1,2)*tt10)/3.0E+0+((-1.0E+1)*F(1,1)*F(2,1)*tt5*tt9)/&
&9.0E+0)-1.0E+0*F(1,1)*lam(1,1)*F(2,1)
hes(1,1) = 5.0E-1*mu(1,1)*(tt12+tt11+(1.0E+1*tt1*tt5*tt9)/9.0E+0)&
&+1.0E+0*lam(1,1)*tt1
hes(1,2) = tt13
hes(1,3) = tt14
hes(1,4) = tt16
hes(2,1) = tt13
hes(2,2) = 5.0E-1*mu(1,1)*(tt12+tt17+(1.0E+1*tt7*tt5*tt9)/9.0E+0)&
&+1.0E+0*lam(1,1)*tt7
hes(2,3) = tt18
hes(2,4) = tt19
hes(3,1) = tt14
hes(3,2) = tt18
hes(3,3) = 5.0E-1*mu(1,1)*(tt12+tt17+(1.0E+1*tt8*tt5*tt9)/9.0E+0)&
&+1.0E+0*lam(1,1)*tt8
hes(3,4) = tt20
hes(4,1) = tt16
hes(4,2) = tt19
hes(4,3) = tt20
hes(4,4) = 5.0E-1*mu(1,1)*(tt12+tt11+(1.0E+1*tt6*tt5*tt9)/9.0E+0)&
&+1.0E+0*tt6*lam(1,1)
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
val(1,1) = 5.0E-1*lam(1,1)*tt1**2+5.0E-1*mu(1,1)*(F(2,2)**2+F(2,1&
&)**2+F(1,2)**2+F(1,1)**2-3)-mu(1,1)*tt1
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*lam(1,1)*F(2,2)*tt1-mu(1,1)*F(2,2)+1.0E+0*F(1,1&
&)*mu(1,1)
jac(1,2) = (-1.0E+0*lam(1,1)*F(1,2)*tt1)+1.0E+0*mu(1,1)*F(2,1)+mu&
&(1,1)*F(1,2)
jac(1,3) = (-1.0E+0*lam(1,1)*F(2,1)*tt1)+mu(1,1)*F(2,1)+1.0E+0*mu&
&(1,1)*F(1,2)
jac(1,4) = 1.0E+0*F(1,1)*lam(1,1)*tt1+1.0E+0*mu(1,1)*F(2,2)-F(1,1&
&)*mu(1,1)
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
REAL(KIND=8)  tt8
tt1 = 1.0E+0*mu(1,1)
tt2 = -1.0E+0*lam(1,1)*F(1,2)*F(2,2)
tt3 = -1.0E+0*lam(1,1)*F(2,1)*F(2,2)
tt4 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt5 = 1.0E+0*lam(1,1)*tt4+1.0E+0*F(1,1)*lam(1,1)*F(2,2)-mu(1,1)
tt6 = (-1.0E+0*lam(1,1)*tt4)+1.0E+0*lam(1,1)*F(1,2)*F(2,1)+mu(1,1&
&)
tt7 = -1.0E+0*F(1,1)*lam(1,1)*F(1,2)
tt8 = -1.0E+0*F(1,1)*lam(1,1)*F(2,1)
hes(1,1) = 1.0E+0*lam(1,1)*F(2,2)**2+tt1
hes(1,2) = tt2
hes(1,3) = tt3
hes(1,4) = tt5
hes(2,1) = tt2
hes(2,2) = 1.0E+0*lam(1,1)*F(1,2)**2+tt1
hes(2,3) = tt6
hes(2,4) = tt7
hes(3,1) = tt3
hes(3,2) = tt6
hes(3,3) = 1.0E+0*lam(1,1)*F(2,1)**2+tt1
hes(3,4) = tt8
hes(4,1) = tt5
hes(4,2) = tt7
hes(4,3) = tt8
hes(4,4) = tt1+1.0E+0*F(1,1)**2*lam(1,1)
END
SUBROUTINE &
&pixar18_neohookean_2d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = F(2,1)**2
tt4 = F(2,2)**2
tt5 = (5.0E+0*mu(1,1))/6.0E+0+lam(1,1)
val(1,1) = (-6.666666666666666E-1*mu(1,1)*log(tt4+tt3+tt2+tt1+1))&
&+5.0E-1*tt5*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-mu(1,1)/tt5-1)**2+6.6666&
&66666666666E-1*mu(1,1)*(tt4+tt3+tt2+tt1-3)
END
SUBROUTINE &
&pixar18_neohookean_2d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = (5.0E+0*mu(1,1))/6.0E+0+lam(1,1)
tt2 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-mu(1,1)/tt1-1
tt3 = 1/(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2+1)
jac(1,1) = (-1.3333333333333333E+0*F(1,1)*mu(1,1)*tt3)+1.0E+0*tt1&
&*F(2,2)*tt2+1.3333333333333333E+0*F(1,1)*mu(1,1)
jac(1,2) = (-1.3333333333333333E+0*mu(1,1)*F(2,1)*tt3)-1.0E+0*tt1&
&*F(1,2)*tt2+1.3333333333333333E+0*mu(1,1)*F(2,1)
jac(1,3) = (-1.3333333333333333E+0*mu(1,1)*F(1,2)*tt3)-1.0E+0*tt1&
&*F(2,1)*tt2+1.3333333333333333E+0*mu(1,1)*F(1,2)
jac(1,4) = (-1.3333333333333333E+0*mu(1,1)*F(2,2)*tt3)+1.0E+0*F(1&
&,1)*tt1*tt2+1.3333333333333333E+0*mu(1,1)*F(2,2)
END
SUBROUTINE &
&pixar18_neohookean_2d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = 1.3333333333333333E+0*mu(1,1)
tt2 = (5.0E+0*mu(1,1))/6.0E+0+lam(1,1)
tt3 = F(2,2)**2
tt4 = F(1,1)**2
tt5 = F(1,2)**2
tt6 = F(2,1)**2
tt7 = tt3+tt6+tt5+tt4+1
tt8 = 1/tt7**2
tt9 = -(1.3333333333333333E+0*mu(1,1))/tt7
tt10 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(2,1)*tt8-1.0E+0*tt2&
&*F(1,2)*F(2,2)
tt11 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(1,2)*tt8-1.0E+0*tt2&
&*F(2,1)*F(2,2)
tt12 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-mu(1,1)/tt2-1
tt13 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(2,2)*tt8+1.0E+0*tt2&
&*tt12+1.0E+0*F(1,1)*tt2*F(2,2)
tt14 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(2,1)*tt8-1.0E+0*tt2&
&*tt12+1.0E+0*tt2*F(1,2)*F(2,1)
tt15 = 2.6666666666666667E+0*mu(1,1)*F(2,1)*F(2,2)*tt8-1.0E+0*F(1&
&,1)*tt2*F(1,2)
tt16 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(2,2)*tt8-1.0E+0*F(1&
&,1)*tt2*F(2,1)
hes(1,1) = tt9+2.6666666666666667E+0*tt4*mu(1,1)*tt8+1.0E+0*tt2*t&
&t3+tt1
hes(1,2) = tt10
hes(1,3) = tt11
hes(1,4) = tt13
hes(2,1) = tt10
hes(2,2) = tt9+2.6666666666666667E+0*mu(1,1)*tt6*tt8+1.0E+0*tt2*t&
&t5+tt1
hes(2,3) = tt14
hes(2,4) = tt15
hes(3,1) = tt11
hes(3,2) = tt14
hes(3,3) = tt9+2.6666666666666667E+0*mu(1,1)*tt5*tt8+1.0E+0*tt2*t&
&t6+tt1
hes(3,4) = tt16
hes(4,1) = tt13
hes(4,2) = tt15
hes(4,3) = tt16
hes(4,4) = tt9+2.6666666666666667E+0*mu(1,1)*tt3*tt8+tt1+1.0E+0*t&
&t4*tt2
END
SUBROUTINE &
&linear_elas_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(1.0E+0*F(2,2)+1.0E+0*F(1,1)-2)**2
END
SUBROUTINE &
&linear_elas_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*(1.0E+0*F(2,2)+1.0E+0*F(1,1)-2)
jac(1,1) = tt1
jac(1,2) = 0
jac(1,3) = 0
jac(1,4) = tt1
END
SUBROUTINE &
&linear_elas_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
hes(1,1) = 1.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 1.0E+0
hes(2,1) = 0
hes(2,2) = 0
hes(2,3) = 0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 0
hes(3,4) = 0
hes(4,1) = 1.0E+0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 1.0E+0
END
SUBROUTINE &
&linear_elas_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = (1.0E+0*F(2,2)-1)**2+5.0E-1*(F(2,1)+F(1,2))**2+(1.0E+0&
&*F(1,1)-1)**2
END
SUBROUTINE &
&linear_elas_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*(F(2,1)+F(1,2))
jac(1,1) = 2.0E+0*(1.0E+0*F(1,1)-1)
jac(1,2) = tt1
jac(1,3) = tt1
jac(1,4) = 2.0E+0*(1.0E+0*F(2,2)-1)
END
SUBROUTINE &
&linear_elas_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
hes(1,1) = 2.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(2,1) = 0
hes(2,2) = 1.0E+0
hes(2,3) = 1.0E+0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 1.0E+0
hes(3,3) = 1.0E+0
hes(3,4) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2.0E+0
END
SUBROUTINE &
&stvk_elas_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(5.0E-1*(F(2,2)**2+F(1,2)**2-1)+5.0E-1*(F(2,1)*&
&*2+F(1,1)**2-1))**2
END
SUBROUTINE &
&stvk_elas_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = 5.0E-1*(F(2,2)**2+F(1,2)**2-1)+5.0E-1*(F(2,1)**2+F(1,1)**2-&
&1)
jac(1,1) = 1.0E+0*F(1,1)*tt1
jac(1,2) = 1.0E+0*F(2,1)*tt1
jac(1,3) = 1.0E+0*F(1,2)*tt1
jac(1,4) = 1.0E+0*F(2,2)*tt1
END
SUBROUTINE &
&stvk_elas_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(1,1)**2
tt2 = F(2,1)**2
tt3 = F(1,2)**2
tt4 = F(2,2)**2
tt5 = 1.0E+0*(5.0E-1*(tt4+tt3-1)+5.0E-1*(tt2+tt1-1))
tt6 = 1.0E+0*F(1,1)*F(2,1)
tt7 = 1.0E+0*F(1,1)*F(1,2)
tt8 = 1.0E+0*F(1,1)*F(2,2)
tt9 = 1.0E+0*F(1,2)*F(2,1)
tt10 = 1.0E+0*F(2,1)*F(2,2)
tt11 = 1.0E+0*F(1,2)*F(2,2)
hes(1,1) = tt5+1.0E+0*tt1
hes(1,2) = tt6
hes(1,3) = tt7
hes(1,4) = tt8
hes(2,1) = tt6
hes(2,2) = tt5+1.0E+0*tt2
hes(2,3) = tt9
hes(2,4) = tt10
hes(3,1) = tt7
hes(3,2) = tt9
hes(3,3) = tt5+1.0E+0*tt3
hes(3,4) = tt11
hes(4,1) = tt8
hes(4,2) = tt10
hes(4,3) = tt11
hes(4,4) = tt5+1.0E+0*tt4
END
SUBROUTINE &
&stvk_elas_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 2.5E-1*(F(2,2)**2+F(1,2)**2-1)**2+5.0E-1*(F(2,1)*F(2,2&
&)+F(1,1)*F(1,2))**2+2.5E-1*(F(2,1)**2+F(1,1)**2-1)**2
END
SUBROUTINE &
&stvk_elas_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,1)**2+F(1,1)**2-1
tt2 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(2,2)**2+F(1,2)**2-1
jac(1,1) = 1.0E+0*F(1,2)*tt2+1.0E+0*F(1,1)*tt1
jac(1,2) = 1.0E+0*F(2,2)*tt2+1.0E+0*F(2,1)*tt1
jac(1,3) = 1.0E+0*F(1,2)*tt3+1.0E+0*F(1,1)*tt2
jac(1,4) = 1.0E+0*F(2,2)*tt3+1.0E+0*F(2,1)*tt2
END
SUBROUTINE &
&stvk_elas_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = F(2,1)**2
tt4 = 1.0E+0*(tt3+tt1-1)
tt5 = 1.0E+0*F(1,2)*F(2,2)+2.0E+0*F(1,1)*F(2,1)
tt6 = 1.0E+0*(F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt7 = tt6+1.0E+0*F(1,1)*F(1,2)
tt8 = 1.0E+0*F(1,2)*F(2,1)
tt9 = F(2,2)**2
tt10 = 1.0E+0*F(1,1)*F(2,2)
tt11 = tt6+1.0E+0*F(2,1)*F(2,2)
tt12 = 1.0E+0*(tt9+tt2-1)
tt13 = 2.0E+0*F(1,2)*F(2,2)+1.0E+0*F(1,1)*F(2,1)
hes(1,1) = tt4+1.0E+0*tt2+2.0E+0*tt1
hes(1,2) = tt5
hes(1,3) = tt7
hes(1,4) = tt8
hes(2,1) = tt5
hes(2,2) = 1.0E+0*tt9+tt4+2.0E+0*tt3
hes(2,3) = tt10
hes(2,4) = tt11
hes(3,1) = tt7
hes(3,2) = tt10
hes(3,3) = tt12+2.0E+0*tt2+1.0E+0*tt1
hes(3,4) = tt13
hes(4,1) = tt8
hes(4,2) = tt11
hes(4,3) = tt13
hes(4,4) = tt12+2.0E+0*tt9+1.0E+0*tt3
END
SUBROUTINE &
&coro_elas_lam_2d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
val(1,1) = 5.0E-1*(5.0E-1*(2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))+5.0E-&
&1*(2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-2)**2
END
SUBROUTINE &
&coro_elas_lam_2d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
tt1 = 5.0E-1*(2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))+5.0E-1*(2*F(2,1)*R&
&(2,1)+2*F(1,1)*R(1,1))-2
jac(1,1) = 1.0E+0*R(1,1)*tt1
jac(1,2) = 1.0E+0*R(2,1)*tt1
jac(1,3) = 1.0E+0*R(1,2)*tt1
jac(1,4) = 1.0E+0*R(2,2)*tt1
END
SUBROUTINE &
&coro_elas_lam_2d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = 1.0E+0*R(1,1)*R(2,1)
tt2 = 1.0E+0*R(1,1)*R(1,2)
tt3 = 1.0E+0*R(1,1)*R(2,2)
tt4 = 1.0E+0*R(1,2)*R(2,1)
tt5 = 1.0E+0*R(2,1)*R(2,2)
tt6 = 1.0E+0*R(1,2)*R(2,2)
hes(1,1) = 1.0E+0*R(1,1)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt3
hes(2,1) = tt1
hes(2,2) = 1.0E+0*R(2,1)**2
hes(2,3) = tt4
hes(2,4) = tt5
hes(3,1) = tt2
hes(3,2) = tt4
hes(3,3) = 1.0E+0*R(1,2)**2
hes(3,4) = tt6
hes(4,1) = tt3
hes(4,2) = tt5
hes(4,3) = tt6
hes(4,4) = 1.0E+0*R(2,2)**2
END
SUBROUTINE &
&coro_elas_mu_2d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
val(1,1) = (1.0E+0*F(2,2)*R(2,2)+1.0E+0*F(1,2)*R(1,2)-1)**2+5.0E-&
&1*(F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2))**2+(1&
&.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1,1)-1)**2
END
SUBROUTINE &
&coro_elas_mu_2d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 1.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1,1)-1
tt2 = F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = 1.0E+0*F(2,2)*R(2,2)+1.0E+0*F(1,2)*R(1,2)-1
jac(1,1) = 1.0E+0*R(1,2)*tt2+2.0E+0*R(1,1)*tt1
jac(1,2) = 1.0E+0*R(2,2)*tt2+2.0E+0*R(2,1)*tt1
jac(1,3) = 2.0E+0*R(1,2)*tt3+1.0E+0*R(1,1)*tt2
jac(1,4) = 2.0E+0*R(2,2)*tt3+1.0E+0*R(2,1)*tt2
END
SUBROUTINE &
&coro_elas_mu_2d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
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
tt1 = R(1,1)**2
tt2 = R(1,2)**2
tt3 = 1.0E+0*R(1,2)*R(2,2)+2.0E+0*R(1,1)*R(2,1)
tt4 = 1.0E+0*R(1,1)*R(1,2)
tt5 = 1.0E+0*R(1,2)*R(2,1)
tt6 = R(2,1)**2
tt7 = R(2,2)**2
tt8 = 1.0E+0*R(1,1)*R(2,2)
tt9 = 1.0E+0*R(2,1)*R(2,2)
tt10 = 2.0E+0*R(1,2)*R(2,2)+1.0E+0*R(1,1)*R(2,1)
hes(1,1) = 1.0E+0*tt2+2.0E+0*tt1
hes(1,2) = tt3
hes(1,3) = tt4
hes(1,4) = tt5
hes(2,1) = tt3
hes(2,2) = 1.0E+0*tt7+2.0E+0*tt6
hes(2,3) = tt8
hes(2,4) = tt9
hes(3,1) = tt4
hes(3,2) = tt8
hes(3,3) = 2.0E+0*tt2+1.0E+0*tt1
hes(3,4) = tt10
hes(4,1) = tt5
hes(4,2) = tt9
hes(4,3) = tt10
hes(4,4) = 2.0E+0*tt7+1.0E+0*tt6
END
SUBROUTINE &
&mcadams_coro_elas_lam_2d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
val(1,1) = 5.0E-1*((-R(2,2))+F(2,2)-R(1,1)+F(1,1))**2
END
SUBROUTINE &
&mcadams_coro_elas_lam_2d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*((-R(2,2))+F(2,2)-R(1,1)+F(1,1))
jac(1,1) = tt1
jac(1,2) = 0
jac(1,3) = 0
jac(1,4) = tt1
END
SUBROUTINE &
&mcadams_coro_elas_lam_2d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
hes(1,1) = 1.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 1.0E+0
hes(2,1) = 0
hes(2,2) = 0
hes(2,3) = 0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 0
hes(3,4) = 0
hes(4,1) = 1.0E+0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 1.0E+0
END
SUBROUTINE &
&mcadams_coro_elas_mu_2d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
val(1,1) = (R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))**2+(R(1,2)-F(1,2))*&
&*2+(R(1,1)-F(1,1))**2
END
SUBROUTINE &
&mcadams_coro_elas_mu_2d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
jac(1,1) = -2*(R(1,1)-F(1,1))
jac(1,2) = -2*(R(2,1)-F(2,1))
jac(1,3) = -2*(R(1,2)-F(1,2))
jac(1,4) = -2*(R(2,2)-F(2,2))
END
SUBROUTINE &
&mcadams_coro_elas_mu_2d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
hes(1,1) = 2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(2,1) = 0
hes(2,2) = 2
hes(2,3) = 0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 2
hes(3,4) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_lam_2d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
val(1,1) = 5.0E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-1)**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_lam_2d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*F(2,2)*tt1
jac(1,2) = -1.0E+0*F(1,2)*tt1
jac(1,3) = -1.0E+0*F(2,1)*tt1
jac(1,4) = 1.0E+0*F(1,1)*tt1
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_lam_2d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = -1.0E+0*F(1,2)*F(2,2)
tt2 = -1.0E+0*F(2,1)*F(2,2)
tt3 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt4 = 1.0E+0*tt3+1.0E+0*F(1,1)*F(2,2)
tt5 = 1.0E+0*F(1,2)*F(2,1)-1.0E+0*tt3
tt6 = -1.0E+0*F(1,1)*F(1,2)
tt7 = -1.0E+0*F(1,1)*F(2,1)
hes(1,1) = 1.0E+0*F(2,2)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt4
hes(2,1) = tt1
hes(2,2) = 1.0E+0*F(1,2)**2
hes(2,3) = tt5
hes(2,4) = tt6
hes(3,1) = tt2
hes(3,2) = tt5
hes(3,3) = 1.0E+0*F(2,1)**2
hes(3,4) = tt7
hes(4,1) = tt4
hes(4,2) = tt6
hes(4,3) = tt7
hes(4,4) = 1.0E+0*F(1,1)**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_mu_2d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
val(1,1) = (R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))**2+(R(1,2)-F(1,2))*&
&*2+(R(1,1)-F(1,1))**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_mu_2d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
jac(1,1) = -2*(R(1,1)-F(1,1))
jac(1,2) = -2*(R(2,1)-F(2,1))
jac(1,3) = -2*(R(1,2)-F(1,2))
jac(1,4) = -2*(R(2,2)-F(2,2))
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_mu_2d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) R(2, 2)
hes(1,1) = 2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(2,1) = 0
hes(2,2) = 2
hes(2,3) = 0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 2
hes(3,4) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2
END
SUBROUTINE &
&bonet08_neohookean_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*log(F(1,1)*F(2,2)-F(1,2)*F(2,1))**2
END
SUBROUTINE &
&bonet08_neohookean_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt2 = 1/tt1
tt3 = log(tt1)
jac(1,1) = 1.0E+0*F(2,2)*tt2*tt3
jac(1,2) = -1.0E+0*F(1,2)*tt2*tt3
jac(1,3) = -1.0E+0*F(2,1)*tt2*tt3
jac(1,4) = 1.0E+0*F(1,1)*tt2*tt3
END
SUBROUTINE &
&bonet08_neohookean_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(2,2)**2
tt2 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt3 = 1/tt2**2
tt4 = log(tt2)
tt5 = 1.0E+0*F(1,2)*F(2,2)*tt3*tt4-1.0E+0*F(1,2)*F(2,2)*tt3
tt6 = 1.0E+0*F(2,1)*F(2,2)*tt3*tt4-1.0E+0*F(2,1)*F(2,2)*tt3
tt7 = 1/tt2
tt8 = 1.0E+0*tt7*tt4-1.0E+0*F(1,1)*F(2,2)*tt3*tt4+1.0E+0*F(1,1)*F&
&(2,2)*tt3
tt9 = F(1,2)**2
tt10 = (-1.0E+0*tt7*tt4)-1.0E+0*F(1,2)*F(2,1)*tt3*tt4+1.0E+0*F(1,&
&2)*F(2,1)*tt3
tt11 = 1.0E+0*F(1,1)*F(1,2)*tt3*tt4-1.0E+0*F(1,1)*F(1,2)*tt3
tt12 = F(2,1)**2
tt13 = 1.0E+0*F(1,1)*F(2,1)*tt3*tt4-1.0E+0*F(1,1)*F(2,1)*tt3
tt14 = F(1,1)**2
hes(1,1) = 1.0E+0*tt1*tt3-1.0E+0*tt1*tt3*tt4
hes(1,2) = tt5
hes(1,3) = tt6
hes(1,4) = tt8
hes(2,1) = tt5
hes(2,2) = 1.0E+0*tt9*tt3-1.0E+0*tt9*tt3*tt4
hes(2,3) = tt10
hes(2,4) = tt11
hes(3,1) = tt6
hes(3,2) = tt10
hes(3,3) = 1.0E+0*tt12*tt3-1.0E+0*tt12*tt3*tt4
hes(3,4) = tt13
hes(4,1) = tt8
hes(4,2) = tt11
hes(4,3) = tt13
hes(4,4) = 1.0E+0*tt14*tt3-1.0E+0*tt14*tt3*tt4
END
SUBROUTINE &
&bonet08_neohookean_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2-3)-log&
&(F(1,1)*F(2,2)-F(1,2)*F(2,1))
END
SUBROUTINE &
&bonet08_neohookean_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = 1/(F(1,1)*F(2,2)-F(1,2)*F(2,1))
jac(1,1) = 1.0E+0*F(1,1)-F(2,2)*tt1
jac(1,2) = F(1,2)*tt1+1.0E+0*F(2,1)
jac(1,3) = F(2,1)*tt1+1.0E+0*F(1,2)
jac(1,4) = 1.0E+0*F(2,2)-F(1,1)*tt1
END
SUBROUTINE &
&bonet08_neohookean_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
REAL(KIND=8)  tt8
REAL(KIND=8)  tt9
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt2 = 1/tt1**2
tt3 = -F(1,2)*F(2,2)*tt2
tt4 = -F(2,1)*F(2,2)*tt2
tt5 = 1/tt1
tt6 = F(1,1)*F(2,2)*tt2-tt5
tt7 = tt5+F(1,2)*F(2,1)*tt2
tt8 = -F(1,1)*F(1,2)*tt2
tt9 = -F(1,1)*F(2,1)*tt2
hes(1,1) = F(2,2)**2*tt2+1.0E+0
hes(1,2) = tt3
hes(1,3) = tt4
hes(1,4) = tt6
hes(2,1) = tt3
hes(2,2) = F(1,2)**2*tt2+1.0E+0
hes(2,3) = tt7
hes(2,4) = tt8
hes(3,1) = tt4
hes(3,2) = tt7
hes(3,3) = F(2,1)**2*tt2+1.0E+0
hes(3,4) = tt9
hes(4,1) = tt6
hes(4,2) = tt8
hes(4,3) = tt9
hes(4,4) = F(1,1)**2*tt2+1.0E+0
END
SUBROUTINE &
&ogden97_neohookean_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-1)**2
END
SUBROUTINE &
&ogden97_neohookean_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*F(2,2)*tt1
jac(1,2) = -1.0E+0*F(1,2)*tt1
jac(1,3) = -1.0E+0*F(2,1)*tt1
jac(1,4) = 1.0E+0*F(1,1)*tt1
END
SUBROUTINE &
&ogden97_neohookean_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = -1.0E+0*F(1,2)*F(2,2)
tt2 = -1.0E+0*F(2,1)*F(2,2)
tt3 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt4 = 1.0E+0*tt3+1.0E+0*F(1,1)*F(2,2)
tt5 = 1.0E+0*F(1,2)*F(2,1)-1.0E+0*tt3
tt6 = -1.0E+0*F(1,1)*F(1,2)
tt7 = -1.0E+0*F(1,1)*F(2,1)
hes(1,1) = 1.0E+0*F(2,2)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt4
hes(2,1) = tt1
hes(2,2) = 1.0E+0*F(1,2)**2
hes(2,3) = tt5
hes(2,4) = tt6
hes(3,1) = tt2
hes(3,2) = tt5
hes(3,3) = 1.0E+0*F(2,1)**2
hes(3,4) = tt7
hes(4,1) = tt4
hes(4,2) = tt6
hes(4,3) = tt7
hes(4,4) = 1.0E+0*F(1,1)**2
END
SUBROUTINE &
&ogden97_neohookean_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2-3)-log&
&(F(1,1)*F(2,2)-F(1,2)*F(2,1))
END
SUBROUTINE &
&ogden97_neohookean_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = 1/(F(1,1)*F(2,2)-F(1,2)*F(2,1))
jac(1,1) = 1.0E+0*F(1,1)-F(2,2)*tt1
jac(1,2) = F(1,2)*tt1+1.0E+0*F(2,1)
jac(1,3) = F(2,1)*tt1+1.0E+0*F(1,2)
jac(1,4) = 1.0E+0*F(2,2)-F(1,1)*tt1
END
SUBROUTINE &
&ogden97_neohookean_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
REAL(KIND=8)  tt8
REAL(KIND=8)  tt9
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt2 = 1/tt1**2
tt3 = -F(1,2)*F(2,2)*tt2
tt4 = -F(2,1)*F(2,2)*tt2
tt5 = 1/tt1
tt6 = F(1,1)*F(2,2)*tt2-tt5
tt7 = tt5+F(1,2)*F(2,1)*tt2
tt8 = -F(1,1)*F(1,2)*tt2
tt9 = -F(1,1)*F(2,1)*tt2
hes(1,1) = F(2,2)**2*tt2+1.0E+0
hes(1,2) = tt3
hes(1,3) = tt4
hes(1,4) = tt6
hes(2,1) = tt3
hes(2,2) = F(1,2)**2*tt2+1.0E+0
hes(2,3) = tt7
hes(2,4) = tt8
hes(3,1) = tt4
hes(3,2) = tt7
hes(3,3) = F(2,1)**2*tt2+1.0E+0
hes(3,4) = tt9
hes(4,1) = tt6
hes(4,2) = tt8
hes(4,3) = tt9
hes(4,4) = F(1,1)**2*tt2+1.0E+0
END
SUBROUTINE &
&bower09_neohookean_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-1)**2
END
SUBROUTINE &
&bower09_neohookean_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*F(2,2)*tt1
jac(1,2) = -1.0E+0*F(1,2)*tt1
jac(1,3) = -1.0E+0*F(2,1)*tt1
jac(1,4) = 1.0E+0*F(1,1)*tt1
END
SUBROUTINE &
&bower09_neohookean_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = -1.0E+0*F(1,2)*F(2,2)
tt2 = -1.0E+0*F(2,1)*F(2,2)
tt3 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt4 = 1.0E+0*tt3+1.0E+0*F(1,1)*F(2,2)
tt5 = 1.0E+0*F(1,2)*F(2,1)-1.0E+0*tt3
tt6 = -1.0E+0*F(1,1)*F(1,2)
tt7 = -1.0E+0*F(1,1)*F(2,1)
hes(1,1) = 1.0E+0*F(2,2)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt4
hes(2,1) = tt1
hes(2,2) = 1.0E+0*F(1,2)**2
hes(2,3) = tt5
hes(2,4) = tt6
hes(3,1) = tt2
hes(3,2) = tt5
hes(3,3) = 1.0E+0*F(2,1)**2
hes(3,4) = tt7
hes(4,1) = tt4
hes(4,2) = tt6
hes(4,3) = tt7
hes(4,4) = 1.0E+0*F(1,1)**2
END
SUBROUTINE &
&bower09_neohookean_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*((F(1,1)*F(2,2)-F(1,2)*F(2,1))**((-2.0E+0)/3.0E&
&+0)*(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2)-3)
END
SUBROUTINE &
&bower09_neohookean_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt2 = tt1**((-5.0E+0)/3.0E+0)
tt3 = F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2
tt4 = tt1**((-2.0E+0)/3.0E+0)
jac(1,1) = 5.0E-1*(2*F(1,1)*tt4+((-2.0E+0)*F(2,2)*tt2*tt3)/3.0E+0&
&)
jac(1,2) = 5.0E-1*(2*F(2,1)*tt4+(2.0E+0*F(1,2)*tt2*tt3)/3.0E+0)
jac(1,3) = 5.0E-1*(2*F(1,2)*tt4+(2.0E+0*F(2,1)*tt2*tt3)/3.0E+0)
jac(1,4) = 5.0E-1*(2*F(2,2)*tt4+((-2.0E+0)*F(1,1)*tt2*tt3)/3.0E+0&
&)
END
SUBROUTINE &
&bower09_neohookean_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(2,2)**2
tt2 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt3 = tt2**((-8.0E+0)/3.0E+0)
tt4 = F(1,1)**2
tt5 = F(1,2)**2
tt6 = F(2,1)**2
tt7 = tt1+tt6+tt5+tt4
tt8 = tt2**((-5.0E+0)/3.0E+0)
tt9 = ((-8.0E+0)*F(1,1)*F(2,2)*tt8)/3.0E+0
tt10 = 2/tt2**(2.0E+0/3.0E+0)
tt11 = 5.0E-1*(((-4.0E+0)*F(2,1)*F(2,2)*tt8)/3.0E+0+(4.0E+0*F(1,1&
&)*F(1,2)*tt8)/3.0E+0+((-1.0E+1)*F(1,2)*F(2,2)*tt3*tt7)/9.0E+0)
tt12 = 5.0E-1*(((-4.0E+0)*F(1,2)*F(2,2)*tt8)/3.0E+0+(4.0E+0*F(1,1&
&)*F(2,1)*tt8)/3.0E+0+((-1.0E+1)*F(2,1)*F(2,2)*tt3*tt7)/9.0E+0)
tt13 = 5.0E-1*(((-4.0E+0)*tt1*tt8)/3.0E+0+((-4.0E+0)*tt4*tt8)/3.0&
&E+0+((-2.0E+0)*tt8*tt7)/3.0E+0+(1.0E+1*F(1,1)*F(2,2)*tt3*tt7)/9.0&
&E+0)
tt14 = (8.0E+0*F(1,2)*F(2,1)*tt8)/3.0E+0
tt15 = 5.0E-1*((4.0E+0*tt6*tt8)/3.0E+0+(4.0E+0*tt5*tt8)/3.0E+0+(2&
&.0E+0*tt8*tt7)/3.0E+0+(1.0E+1*F(1,2)*F(2,1)*tt3*tt7)/9.0E+0)
tt16 = 5.0E-1*((4.0E+0*F(1,2)*F(2,2)*tt8)/3.0E+0+((-4.0E+0)*F(1,1&
&)*F(2,1)*tt8)/3.0E+0+((-1.0E+1)*F(1,1)*F(1,2)*tt3*tt7)/9.0E+0)
tt17 = 5.0E-1*((4.0E+0*F(2,1)*F(2,2)*tt8)/3.0E+0+((-4.0E+0)*F(1,1&
&)*F(1,2)*tt8)/3.0E+0+((-1.0E+1)*F(1,1)*F(2,1)*tt3*tt7)/9.0E+0)
hes(1,1) = 5.0E-1*(tt10+tt9+(1.0E+1*tt1*tt3*tt7)/9.0E+0)
hes(1,2) = tt11
hes(1,3) = tt12
hes(1,4) = tt13
hes(2,1) = tt11
hes(2,2) = 5.0E-1*(tt10+tt14+(1.0E+1*tt5*tt3*tt7)/9.0E+0)
hes(2,3) = tt15
hes(2,4) = tt16
hes(3,1) = tt12
hes(3,2) = tt15
hes(3,3) = 5.0E-1*(tt10+tt14+(1.0E+1*tt6*tt3*tt7)/9.0E+0)
hes(3,4) = tt17
hes(4,1) = tt13
hes(4,2) = tt16
hes(4,3) = tt17
hes(4,4) = 5.0E-1*(tt10+tt9+(1.0E+1*tt4*tt3*tt7)/9.0E+0)
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-1)**2
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*F(2,2)*tt1
jac(1,2) = -1.0E+0*F(1,2)*tt1
jac(1,3) = -1.0E+0*F(2,1)*tt1
jac(1,4) = 1.0E+0*F(1,1)*tt1
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = -1.0E+0*F(1,2)*F(2,2)
tt2 = -1.0E+0*F(2,1)*F(2,2)
tt3 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt4 = 1.0E+0*tt3+1.0E+0*F(1,1)*F(2,2)
tt5 = 1.0E+0*F(1,2)*F(2,1)-1.0E+0*tt3
tt6 = -1.0E+0*F(1,1)*F(1,2)
tt7 = -1.0E+0*F(1,1)*F(2,1)
hes(1,1) = 1.0E+0*F(2,2)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt4
hes(2,1) = tt1
hes(2,2) = 1.0E+0*F(1,2)**2
hes(2,3) = tt5
hes(2,4) = tt6
hes(3,1) = tt2
hes(3,2) = tt5
hes(3,3) = 1.0E+0*F(2,1)**2
hes(3,4) = tt7
hes(4,1) = tt4
hes(4,2) = tt6
hes(4,3) = tt7
hes(4,4) = 1.0E+0*F(1,1)**2
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2-3)-F(1&
&,1)*F(2,2)+F(1,2)*F(2,1)+1
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
jac(1,1) = 1.0E+0*F(1,1)-F(2,2)
jac(1,2) = 1.0E+0*F(2,1)+F(1,2)
jac(1,3) = F(2,1)+1.0E+0*F(1,2)
jac(1,4) = 1.0E+0*F(2,2)-F(1,1)
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
hes(1,1) = 1.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = -1
hes(2,1) = 0
hes(2,2) = 1.0E+0
hes(2,3) = 1
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 1
hes(3,3) = 1.0E+0
hes(3,4) = 0
hes(4,1) = -1
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 1.0E+0
END
SUBROUTINE &
&pixar18_neohookean_lam_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = 5.0E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-1)**2
END
SUBROUTINE &
&pixar18_neohookean_lam_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
jac(1,1) = 1.0E+0*F(2,2)*tt1
jac(1,2) = -1.0E+0*F(1,2)*tt1
jac(1,3) = -1.0E+0*F(2,1)*tt1
jac(1,4) = 1.0E+0*F(1,1)*tt1
END
SUBROUTINE &
&pixar18_neohookean_lam_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = -1.0E+0*F(1,2)*F(2,2)
tt2 = -1.0E+0*F(2,1)*F(2,2)
tt3 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt4 = 1.0E+0*tt3+1.0E+0*F(1,1)*F(2,2)
tt5 = 1.0E+0*F(1,2)*F(2,1)-1.0E+0*tt3
tt6 = -1.0E+0*F(1,1)*F(1,2)
tt7 = -1.0E+0*F(1,1)*F(2,1)
hes(1,1) = 1.0E+0*F(2,2)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt4
hes(2,1) = tt1
hes(2,2) = 1.0E+0*F(1,2)**2
hes(2,3) = tt5
hes(2,4) = tt6
hes(3,1) = tt2
hes(3,2) = tt5
hes(3,3) = 1.0E+0*F(2,1)**2
hes(3,4) = tt7
hes(4,1) = tt4
hes(4,2) = tt6
hes(4,3) = tt7
hes(4,4) = 1.0E+0*F(1,1)**2
END
SUBROUTINE &
&pixar18_neohookean_mu_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = F(2,1)**2
tt4 = F(2,2)**2
val(1,1) = (2.0E+0*((-log(tt4+tt3+tt2+tt1+1))+tt4+tt3+tt2+tt1))/3&
&.0E+0+4.166666666666667E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1)-1)**2-F(1&
&,1)*F(2,2)+F(1,2)*F(2,1)
END
SUBROUTINE &
&pixar18_neohookean_mu_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
tt1 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt2 = 1/(F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2+1)
jac(1,1) = (2.0E+0*(2*F(1,1)-2*F(1,1)*tt2))/3.0E+0+8.333333333333&
&334E-1*F(2,2)*tt1-F(2,2)
jac(1,2) = (2.0E+0*(2*F(2,1)-2*F(2,1)*tt2))/3.0E+0-8.333333333333&
&334E-1*F(1,2)*tt1+F(1,2)
jac(1,3) = (2.0E+0*(2*F(1,2)-2*F(1,2)*tt2))/3.0E+0-8.333333333333&
&334E-1*F(2,1)*tt1+F(2,1)
jac(1,4) = (2.0E+0*(2*F(2,2)-2*F(2,2)*tt2))/3.0E+0+8.333333333333&
&334E-1*F(1,1)*tt1-F(1,1)
END
SUBROUTINE &
&pixar18_neohookean_mu_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(2,2)**2
tt2 = F(1,1)**2
tt3 = F(1,2)**2
tt4 = F(2,1)**2
tt5 = tt1+tt4+tt3+tt2+1
tt6 = 1/tt5**2
tt7 = -2/tt5
tt8 = (8.0E+0*F(1,1)*F(2,1)*tt6)/3.0E+0-8.333333333333334E-1*F(1,&
&2)*F(2,2)
tt9 = (8.0E+0*F(1,1)*F(1,2)*tt6)/3.0E+0-8.333333333333334E-1*F(2,&
&1)*F(2,2)
tt10 = F(1,1)*F(2,2)-F(1,2)*F(2,1)-1
tt11 = (8.0E+0*F(1,1)*F(2,2)*tt6)/3.0E+0+8.333333333333334E-1*tt1&
&0+8.333333333333334E-1*F(1,1)*F(2,2)-1
tt12 = (8.0E+0*F(1,2)*F(2,1)*tt6)/3.0E+0-8.333333333333334E-1*tt1&
&0+8.333333333333334E-1*F(1,2)*F(2,1)+1
tt13 = (8.0E+0*F(2,1)*F(2,2)*tt6)/3.0E+0-8.333333333333334E-1*F(1&
&,1)*F(1,2)
tt14 = (8.0E+0*F(1,2)*F(2,2)*tt6)/3.0E+0-8.333333333333334E-1*F(1&
&,1)*F(2,1)
hes(1,1) = (2.0E+0*(tt7+4*tt2*tt6+2))/3.0E+0+8.333333333333334E-1&
&*tt1
hes(1,2) = tt8
hes(1,3) = tt9
hes(1,4) = tt11
hes(2,1) = tt8
hes(2,2) = (2.0E+0*(tt7+4*tt4*tt6+2))/3.0E+0+8.333333333333334E-1&
&*tt3
hes(2,3) = tt12
hes(2,4) = tt13
hes(3,1) = tt9
hes(3,2) = tt12
hes(3,3) = (2.0E+0*(tt7+4*tt3*tt6+2))/3.0E+0+8.333333333333334E-1&
&*tt4
hes(3,4) = tt14
hes(4,1) = tt11
hes(4,2) = tt13
hes(4,3) = tt14
hes(4,4) = (2.0E+0*(tt7+4*tt1*tt6+2))/3.0E+0+8.333333333333334E-1&
&*tt2
END
SUBROUTINE &
&small_general_linear_elas_2d_val(&
&  val &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 1.0E+0*F(1,1)-1
tt2 = F(2,1)+F(1,2)
tt3 = 1.0E+0*F(2,2)-1
val(1,1) = 5.0E-1*(1.0E+0*tt2*(1.0E+0*tt2*C(3,3)+tt3*C(3,2)+tt1*C&
&(3,1))+tt3*(1.0E+0*tt2*C(2,3)+C(2,2)*tt3+tt1*C(2,1))+tt1*(C(1,2)*&
&tt3+1.0E+0*C(1,3)*tt2+C(1,1)*tt1))
END
SUBROUTINE &
&small_general_linear_elas_2d_jac(&
&  jac &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
tt1 = 1.0E+0*F(1,1)-1
tt2 = 1.0E+0*F(2,2)-1
tt3 = F(2,1)+F(1,2)
tt4 = 1.0E+0*tt3*C(3,3)
tt5 = 5.0E-1*(1.0E+0*(tt4+tt2*C(3,2)+tt1*C(3,1))+tt4+1.0E+0*tt2*C&
&(2,3)+1.0E+0*tt1*C(1,3))
jac(1,1) = 5.0E-1*(1.0E+0*tt3*C(3,1)+1.0E+0*(C(1,2)*tt2+1.0E+0*C(&
&1,3)*tt3+C(1,1)*tt1)+1.0E+0*C(2,1)*tt2+1.0E+0*C(1,1)*tt1)
jac(1,2) = tt5
jac(1,3) = tt5
jac(1,4) = 5.0E-1*(1.0E+0*tt3*C(3,2)+1.0E+0*(1.0E+0*tt3*C(2,3)+C(&
&2,2)*tt2+tt1*C(2,1))+1.0E+0*C(2,2)*tt2+1.0E+0*tt1*C(1,2))
END
SUBROUTINE &
&small_general_linear_elas_2d_hes(&
&  hes &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
tt1 = 5.0E-1*(1.0E+0*C(3,1)+1.0E+0*C(1,3))
tt2 = 5.0E-1*(1.0E+0*C(2,1)+1.0E+0*C(1,2))
tt3 = 1.0E+0*C(3,3)
tt4 = 5.0E-1*(1.0E+0*C(3,2)+1.0E+0*C(2,3))
hes(1,1) = 1.0E+0*C(1,1)
hes(1,2) = tt1
hes(1,3) = tt1
hes(1,4) = tt2
hes(2,1) = tt1
hes(2,2) = tt3
hes(2,3) = tt3
hes(2,4) = tt4
hes(3,1) = tt1
hes(3,2) = tt3
hes(3,3) = tt3
hes(3,4) = tt4
hes(4,1) = tt2
hes(4,2) = tt4
hes(4,3) = tt4
hes(4,4) = 1.0E+0*C(2,2)
END
SUBROUTINE &
&green_general_linear_elas_2d_val(&
&  val &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,1)**2+F(1,1)**2-1
tt2 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(2,2)**2+F(1,2)**2-1
val(1,1) = 5.0E-1*(1.0E+0*tt2*(1.0E+0*tt2*C(3,3)+5.0E-1*tt3*C(3,2&
&)+5.0E-1*tt1*C(3,1))+5.0E-1*tt3*(1.0E+0*tt2*C(2,3)+5.0E-1*C(2,2)*&
&tt3+5.0E-1*C(2,1)*tt1)+5.0E-1*tt1*(5.0E-1*C(1,2)*tt3+1.0E+0*C(1,3&
&)*tt2+5.0E-1*C(1,1)*tt1))
END
SUBROUTINE &
&green_general_linear_elas_2d_jac(&
&  jac &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = F(2,1)**2+F(1,1)**2-1
tt2 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(2,2)**2+F(1,2)**2-1
tt4 = 5.0E-1*C(1,2)*tt3+1.0E+0*C(1,3)*tt2+5.0E-1*C(1,1)*tt1
tt5 = 1.0E+0*tt2*C(3,3)+5.0E-1*tt3*C(3,2)+5.0E-1*tt1*C(3,1)
tt6 = 1.0E+0*tt2*C(2,3)+5.0E-1*C(2,2)*tt3+5.0E-1*C(2,1)*tt1
jac(1,1) = 5.0E-1*(1.0E+0*F(1,2)*tt5+1.0E+0*tt2*(1.0E+0*F(1,2)*C(&
&3,3)+1.0E+0*F(1,1)*C(3,1))+5.0E-1*tt3*(1.0E+0*F(1,2)*C(2,3)+1.0E+&
&0*F(1,1)*C(2,1))+1.0E+0*F(1,1)*tt4+5.0E-1*(1.0E+0*F(1,2)*C(1,3)+1&
&.0E+0*C(1,1)*F(1,1))*tt1)
jac(1,2) = 5.0E-1*(1.0E+0*F(2,2)*tt5+1.0E+0*tt2*(1.0E+0*F(2,2)*C(&
&3,3)+1.0E+0*F(2,1)*C(3,1))+5.0E-1*tt3*(1.0E+0*F(2,2)*C(2,3)+1.0E+&
&0*C(2,1)*F(2,1))+1.0E+0*F(2,1)*tt4+5.0E-1*tt1*(1.0E+0*C(1,3)*F(2,&
&2)+1.0E+0*C(1,1)*F(2,1)))
jac(1,3) = 5.0E-1*(1.0E+0*F(1,1)*tt5+1.0E+0*tt2*(1.0E+0*F(1,1)*C(&
&3,3)+1.0E+0*F(1,2)*C(3,2))+1.0E+0*F(1,2)*tt6+5.0E-1*tt3*(1.0E+0*F&
&(1,1)*C(2,3)+1.0E+0*F(1,2)*C(2,2))+5.0E-1*(1.0E+0*F(1,1)*C(1,3)+1&
&.0E+0*C(1,2)*F(1,2))*tt1)
jac(1,4) = 5.0E-1*(1.0E+0*F(2,1)*tt5+1.0E+0*tt2*(1.0E+0*F(2,1)*C(&
&3,3)+1.0E+0*F(2,2)*C(3,2))+1.0E+0*F(2,2)*tt6+5.0E-1*tt3*(1.0E+0*F&
&(2,1)*C(2,3)+1.0E+0*C(2,2)*F(2,2))+5.0E-1*tt1*(1.0E+0*C(1,2)*F(2,&
&2)+1.0E+0*C(1,3)*F(2,1)))
END
SUBROUTINE &
&green_general_linear_elas_2d_hes(&
&  hes &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
tt1 = 1.0E+0*F(1,2)*C(1,3)+1.0E+0*C(1,1)*F(1,1)
tt2 = F(2,1)**2+F(1,1)**2-1
tt3 = 5.0E-1*C(1,1)*tt2
tt4 = F(2,2)**2+F(1,2)**2-1
tt5 = 5.0E-1*C(2,1)*tt4
tt6 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt7 = 1.0E+0*(5.0E-1*C(1,2)*tt4+1.0E+0*C(1,3)*tt6+tt3)
tt8 = 1.0E+0*tt6*C(3,1)
tt9 = 1.0E+0*F(1,2)*C(3,3)+1.0E+0*F(1,1)*C(3,1)
tt10 = 1.0E+0*C(1,3)*F(2,2)+1.0E+0*C(1,1)*F(2,1)
tt11 = 1.0E+0*F(2,2)*C(3,3)+1.0E+0*F(2,1)*C(3,1)
tt12 = 5.0E-1*(1.0E+0*F(1,2)*tt11+1.0E+0*F(2,2)*tt9+1.0E+0*F(1,1)&
&*tt10+1.0E+0*tt1*F(2,1))
tt13 = 1.0E+0*F(1,1)*C(1,3)+1.0E+0*C(1,2)*F(1,2)
tt14 = 5.0E-1*C(1,3)*tt2
tt15 = 5.0E-1*tt4*C(2,3)
tt16 = 1.0E+0*F(1,2)*C(2,3)+1.0E+0*F(1,1)*C(2,1)
tt17 = 1.0E+0*tt6*C(3,3)
tt18 = 1.0E+0*F(1,1)*C(3,3)+1.0E+0*F(1,2)*C(3,2)
tt19 = 1.0E+0*(tt17+5.0E-1*tt4*C(3,2)+5.0E-1*tt2*C(3,1))
tt20 = 5.0E-1*(tt19+1.0E+0*F(1,1)*tt9+1.0E+0*F(1,2)*tt18+tt17+1.0&
&E+0*F(1,2)*tt16+tt15+tt14+1.0E+0*F(1,1)*tt13)
tt21 = 1.0E+0*C(1,2)*F(2,2)+1.0E+0*C(1,3)*F(2,1)
tt22 = 1.0E+0*F(2,1)*C(3,3)+1.0E+0*F(2,2)*C(3,2)
tt23 = 5.0E-1*(1.0E+0*F(1,2)*tt22+1.0E+0*F(2,1)*tt9+1.0E+0*F(2,2)&
&*tt16+1.0E+0*F(1,1)*tt21)
tt24 = 1.0E+0*F(2,2)*C(2,3)+1.0E+0*C(2,1)*F(2,1)
tt25 = 5.0E-1*(1.0E+0*F(1,1)*tt11+1.0E+0*F(2,2)*tt18+1.0E+0*F(1,2&
&)*tt24+1.0E+0*tt13*F(2,1))
tt26 = 5.0E-1*(tt19+1.0E+0*F(2,1)*tt11+1.0E+0*F(2,2)*tt22+tt17+1.&
&0E+0*F(2,2)*tt24+tt15+1.0E+0*F(2,1)*tt21+tt14)
tt27 = 5.0E-1*C(1,2)*tt2
tt28 = 5.0E-1*C(2,2)*tt4
tt29 = 1.0E+0*F(1,1)*C(2,3)+1.0E+0*F(1,2)*C(2,2)
tt30 = 1.0E+0*(1.0E+0*tt6*C(2,3)+tt28+5.0E-1*C(2,1)*tt2)
tt31 = 1.0E+0*tt6*C(3,2)
tt32 = 1.0E+0*F(2,1)*C(2,3)+1.0E+0*C(2,2)*F(2,2)
tt33 = 5.0E-1*(1.0E+0*F(1,1)*tt22+1.0E+0*F(2,1)*tt18+1.0E+0*F(1,2&
&)*tt32+1.0E+0*F(2,2)*tt29)
hes(1,1) = 5.0E-1*(2.0E+0*F(1,2)*tt9+tt8+tt7+tt5+tt3+2.0E+0*F(1,1&
&)*tt1)
hes(1,2) = tt12
hes(1,3) = tt20
hes(1,4) = tt23
hes(2,1) = tt12
hes(2,2) = 5.0E-1*(2.0E+0*F(2,2)*tt11+tt8+tt7+tt5+2.0E+0*F(2,1)*t&
&t10+tt3)
hes(2,3) = tt25
hes(2,4) = tt26
hes(3,1) = tt20
hes(3,2) = tt25
hes(3,3) = 5.0E-1*(2.0E+0*F(1,1)*tt18+tt31+tt30+2.0E+0*F(1,2)*tt2&
&9+tt28+tt27)
hes(3,4) = tt33
hes(4,1) = tt23
hes(4,2) = tt26
hes(4,3) = tt33
hes(4,4) = 5.0E-1*(2.0E+0*F(2,1)*tt22+tt31+tt30+2.0E+0*F(2,2)*tt3&
&2+tt28+tt27)
END
SUBROUTINE &
&coro_general_linear_elas_2d_val(&
&  val &
&, F &
&, C &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 5.0E-1*(2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-1
tt2 = F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = 5.0E-1*(2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))-1
val(1,1) = 5.0E-1*(1.0E+0*tt2*(1.0E+0*tt2*C(3,3)+tt3*C(3,2)+tt1*C&
&(3,1))+tt3*(1.0E+0*tt2*C(2,3)+C(2,2)*tt3+C(2,1)*tt1)+tt1*(C(1,2)*&
&tt3+1.0E+0*C(1,3)*tt2+C(1,1)*tt1))
END
SUBROUTINE &
&coro_general_linear_elas_2d_jac(&
&  jac &
&, F &
&, C &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8) R(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = 5.0E-1*(2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-1
tt2 = F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = 5.0E-1*(2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))-1
tt4 = C(1,2)*tt3+1.0E+0*C(1,3)*tt2+C(1,1)*tt1
tt5 = 1.0E+0*tt2*C(3,3)+tt3*C(3,2)+tt1*C(3,1)
tt6 = 1.0E+0*tt2*C(2,3)+C(2,2)*tt3+C(2,1)*tt1
jac(1,1) = 5.0E-1*(1.0E+0*R(1,2)*tt5+1.0E+0*tt2*(1.0E+0*R(1,2)*C(&
&3,3)+1.0E+0*R(1,1)*C(3,1))+tt3*(1.0E+0*R(1,2)*C(2,3)+1.0E+0*R(1,1&
&)*C(2,1))+1.0E+0*R(1,1)*tt4+(1.0E+0*R(1,2)*C(1,3)+1.0E+0*C(1,1)*R&
&(1,1))*tt1)
jac(1,2) = 5.0E-1*(1.0E+0*R(2,2)*tt5+1.0E+0*tt2*(1.0E+0*R(2,2)*C(&
&3,3)+1.0E+0*R(2,1)*C(3,1))+tt3*(1.0E+0*R(2,2)*C(2,3)+1.0E+0*C(2,1&
&)*R(2,1))+1.0E+0*R(2,1)*tt4+tt1*(1.0E+0*C(1,3)*R(2,2)+1.0E+0*C(1,&
&1)*R(2,1)))
jac(1,3) = 5.0E-1*(1.0E+0*R(1,1)*tt5+1.0E+0*tt2*(1.0E+0*R(1,1)*C(&
&3,3)+1.0E+0*R(1,2)*C(3,2))+1.0E+0*R(1,2)*tt6+tt3*(1.0E+0*R(1,1)*C&
&(2,3)+1.0E+0*R(1,2)*C(2,2))+(1.0E+0*R(1,1)*C(1,3)+1.0E+0*C(1,2)*R&
&(1,2))*tt1)
jac(1,4) = 5.0E-1*(1.0E+0*R(2,1)*tt5+1.0E+0*tt2*(1.0E+0*R(2,1)*C(&
&3,3)+1.0E+0*R(2,2)*C(3,2))+1.0E+0*R(2,2)*tt6+tt3*(1.0E+0*R(2,1)*C&
&(2,3)+1.0E+0*C(2,2)*R(2,2))+tt1*(1.0E+0*C(1,2)*R(2,2)+1.0E+0*C(1,&
&3)*R(2,1)))
END
SUBROUTINE &
&coro_general_linear_elas_2d_hes(&
&  hes &
&, F &
&, C &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8) C(3, 3)
REAL(KIND=8) R(2, 2)
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
tt1 = 1.0E+0*R(1,2)*C(1,3)+1.0E+0*C(1,1)*R(1,1)
tt2 = 1.0E+0*R(1,2)*C(3,3)+1.0E+0*R(1,1)*C(3,1)
tt3 = 1.0E+0*C(1,3)*R(2,2)+1.0E+0*C(1,1)*R(2,1)
tt4 = 1.0E+0*R(2,2)*C(3,3)+1.0E+0*R(2,1)*C(3,1)
tt5 = 5.0E-1*(1.0E+0*R(1,2)*tt4+1.0E+0*R(2,2)*tt2+1.0E+0*R(1,1)*t&
&t3+1.0E+0*tt1*R(2,1))
tt6 = 1.0E+0*R(1,1)*C(1,3)+1.0E+0*C(1,2)*R(1,2)
tt7 = 1.0E+0*R(1,2)*C(2,3)+1.0E+0*R(1,1)*C(2,1)
tt8 = 1.0E+0*R(1,1)*C(3,3)+1.0E+0*R(1,2)*C(3,2)
tt9 = 5.0E-1*(1.0E+0*R(1,1)*tt2+1.0E+0*R(1,2)*tt8+1.0E+0*R(1,2)*t&
&t7+1.0E+0*R(1,1)*tt6)
tt10 = 1.0E+0*C(1,2)*R(2,2)+1.0E+0*C(1,3)*R(2,1)
tt11 = 1.0E+0*R(2,1)*C(3,3)+1.0E+0*R(2,2)*C(3,2)
tt12 = 5.0E-1*(1.0E+0*R(1,2)*tt11+1.0E+0*R(2,1)*tt2+1.0E+0*R(2,2)&
&*tt7+1.0E+0*R(1,1)*tt10)
tt13 = 1.0E+0*R(2,2)*C(2,3)+1.0E+0*C(2,1)*R(2,1)
tt14 = 5.0E-1*(1.0E+0*R(1,1)*tt4+1.0E+0*R(2,2)*tt8+1.0E+0*R(1,2)*&
&tt13+1.0E+0*tt6*R(2,1))
tt15 = 5.0E-1*(1.0E+0*R(2,1)*tt4+1.0E+0*R(2,2)*tt11+1.0E+0*R(2,2)&
&*tt13+1.0E+0*R(2,1)*tt10)
tt16 = 1.0E+0*R(1,1)*C(2,3)+1.0E+0*R(1,2)*C(2,2)
tt17 = 1.0E+0*R(2,1)*C(2,3)+1.0E+0*C(2,2)*R(2,2)
tt18 = 5.0E-1*(1.0E+0*R(1,1)*tt11+1.0E+0*R(2,1)*tt8+1.0E+0*R(1,2)&
&*tt17+1.0E+0*R(2,2)*tt16)
hes(1,1) = 5.0E-1*(2.0E+0*R(1,2)*tt2+2.0E+0*R(1,1)*tt1)
hes(1,2) = tt5
hes(1,3) = tt9
hes(1,4) = tt12
hes(2,1) = tt5
hes(2,2) = 5.0E-1*(2.0E+0*R(2,2)*tt4+2.0E+0*R(2,1)*tt3)
hes(2,3) = tt14
hes(2,4) = tt15
hes(3,1) = tt9
hes(3,2) = tt14
hes(3,3) = 5.0E-1*(2.0E+0*R(1,1)*tt8+2.0E+0*R(1,2)*tt16)
hes(3,4) = tt18
hes(4,1) = tt12
hes(4,2) = tt15
hes(4,3) = tt18
hes(4,4) = 5.0E-1*(2.0E+0*R(2,1)*tt11+2.0E+0*R(2,2)*tt17)
END
SUBROUTINE &
&I_C_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = F(2,2)**2+F(2,1)**2+F(1,2)**2+F(1,1)**2
END
SUBROUTINE &
&I_C_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
jac(1,1) = 2*F(1,1)
jac(1,2) = 2*F(2,1)
jac(1,3) = 2*F(1,2)
jac(1,4) = 2*F(2,2)
END
SUBROUTINE &
&I_C_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
hes(1,1) = 2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(2,1) = 0
hes(2,2) = 2
hes(2,3) = 0
hes(2,4) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 2
hes(3,4) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2
END
SUBROUTINE &
&II_C_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = (F(2,2)**2+F(1,2)**2)**2+2*(F(2,1)*F(2,2)+F(1,1)*F(1,2&
&))**2+(F(2,1)**2+F(1,1)**2)**2
END
SUBROUTINE &
&II_C_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,1)**2+F(1,1)**2
tt2 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(2,2)**2+F(1,2)**2
jac(1,1) = 4*F(1,2)*tt2+4*F(1,1)*tt1
jac(1,2) = 4*F(2,2)*tt2+4*F(2,1)*tt1
jac(1,3) = 4*F(1,2)*tt3+4*F(1,1)*tt2
jac(1,4) = 4*F(2,2)*tt3+4*F(2,1)*tt2
END
SUBROUTINE &
&II_C_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = F(2,1)**2
tt4 = 4*(tt3+tt1)
tt5 = 4*F(1,2)*F(2,2)+8*F(1,1)*F(2,1)
tt6 = 4*(F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt7 = tt6+4*F(1,1)*F(1,2)
tt8 = 4*F(1,2)*F(2,1)
tt9 = F(2,2)**2
tt10 = 4*F(1,1)*F(2,2)
tt11 = tt6+4*F(2,1)*F(2,2)
tt12 = 4*(tt9+tt2)
tt13 = 8*F(1,2)*F(2,2)+4*F(1,1)*F(2,1)
hes(1,1) = tt4+4*tt2+8*tt1
hes(1,2) = tt5
hes(1,3) = tt7
hes(1,4) = tt8
hes(2,1) = tt5
hes(2,2) = 4*tt9+tt4+8*tt3
hes(2,3) = tt10
hes(2,4) = tt11
hes(3,1) = tt7
hes(3,2) = tt10
hes(3,3) = tt12+8*tt2+4*tt1
hes(3,4) = tt13
hes(4,1) = tt8
hes(4,2) = tt11
hes(4,3) = tt13
hes(4,4) = tt12+8*tt9+4*tt3
END
SUBROUTINE &
&III_C_2d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(2, 2)
val(1,1) = (F(2,1)**2+F(1,1)**2)*(F(2,2)**2+F(1,2)**2)-(F(2,1)*F(&
&2,2)+F(1,1)*F(1,2))**2
END
SUBROUTINE &
&III_C_2d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 4)
REAL(KIND=8) F(2, 2)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt2 = F(2,2)**2+F(1,2)**2
tt3 = F(2,1)**2+F(1,1)**2
jac(1,1) = 2*F(1,1)*tt2-2*F(1,2)*tt1
jac(1,2) = 2*F(2,1)*tt2-2*F(2,2)*tt1
jac(1,3) = 2*F(1,2)*tt3-2*F(1,1)*tt1
jac(1,4) = 2*tt3*F(2,2)-2*F(2,1)*tt1
END
SUBROUTINE &
&III_C_2d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(4, 4)
REAL(KIND=8) F(2, 2)
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
tt1 = F(1,2)**2
tt2 = F(2,2)**2
tt3 = 2*(tt2+tt1)
tt4 = -2*F(1,2)*F(2,2)
tt5 = -2*(F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt6 = tt5+2*F(1,1)*F(1,2)
tt7 = 4*F(1,1)*F(2,2)-2*F(1,2)*F(2,1)
tt8 = 4*F(1,2)*F(2,1)-2*F(1,1)*F(2,2)
tt9 = tt5+2*F(2,1)*F(2,2)
tt10 = F(1,1)**2
tt11 = F(2,1)**2
tt12 = 2*(tt11+tt10)
tt13 = -2*F(1,1)*F(2,1)
hes(1,1) = tt3-2*tt1
hes(1,2) = tt4
hes(1,3) = tt6
hes(1,4) = tt7
hes(2,1) = tt4
hes(2,2) = tt3-2*tt2
hes(2,3) = tt8
hes(2,4) = tt9
hes(3,1) = tt6
hes(3,2) = tt8
hes(3,3) = tt12-2*tt10
hes(3,4) = tt13
hes(4,1) = tt7
hes(4,2) = tt9
hes(4,3) = tt13
hes(4,4) = tt12-2*tt11
END
SUBROUTINE &
&linear_elas_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 1.0E+0*F(1,1)
tt2 = 1.0E+0*F(2,2)
tt3 = 1.0E+0*F(3,3)
val(1,1) = 5.0E-1*lam(1,1)*(tt3+tt2+tt1-3)**2+mu(1,1)*((tt3-1)**2&
&+5.0E-1*(F(3,2)+F(2,3))**2+5.0E-1*(F(3,1)+F(1,3))**2+(tt2-1)**2+5&
&.0E-1*(F(2,1)+F(1,2))**2+(tt1-1)**2)
END
SUBROUTINE &
&linear_elas_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = 1.0E+0*F(1,1)
tt2 = 1.0E+0*F(2,2)
tt3 = 1.0E+0*F(3,3)
tt4 = 1.0E+0*lam(1,1)*(tt3+tt2+tt1-3)
tt5 = 1.0E+0*mu(1,1)*(F(2,1)+F(1,2))
tt6 = 1.0E+0*mu(1,1)*(F(3,1)+F(1,3))
tt7 = 1.0E+0*mu(1,1)*(F(3,2)+F(2,3))
jac(1,1) = tt4+2.0E+0*(tt1-1)*mu(1,1)
jac(1,2) = tt5
jac(1,3) = tt6
jac(1,4) = tt5
jac(1,5) = tt4+2.0E+0*mu(1,1)*(tt2-1)
jac(1,6) = tt7
jac(1,7) = tt6
jac(1,8) = tt7
jac(1,9) = tt4+2.0E+0*mu(1,1)*(tt3-1)
END
SUBROUTINE &
&linear_elas_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = 1.0E+0*lam(1,1)
tt2 = 2.0E+0*mu(1,1)+tt1
tt3 = 1.0E+0*mu(1,1)
hes(1,1) = tt2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = tt1
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = tt1
hes(2,1) = 0
hes(2,2) = tt3
hes(2,3) = 0
hes(2,4) = tt3
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = tt3
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = tt3
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = tt3
hes(4,3) = 0
hes(4,4) = tt3
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = tt1
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = tt2
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = tt1
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = tt3
hes(6,7) = 0
hes(6,8) = tt3
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = tt3
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = tt3
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = tt3
hes(8,7) = 0
hes(8,8) = tt3
hes(8,9) = 0
hes(9,1) = tt1
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = tt1
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = tt2
END
SUBROUTINE &
&stvk_elas_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(3,1)**2+F(2,1)**2+F(1,1)**2-1
tt2 = F(3,2)**2+F(2,2)**2+F(1,2)**2-1
tt3 = F(3,3)**2+F(2,3)**2+F(1,3)**2-1
val(1,1) = 5.0E-1*lam(1,1)*(5.0E-1*tt3+5.0E-1*tt2+5.0E-1*tt1)**2+&
&mu(1,1)*(2.5E-1*tt3**2+5.0E-1*(F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)&
&*F(1,3))**2+5.0E-1*(F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3))**2&
&+2.5E-1*tt2**2+5.0E-1*(F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2))&
&**2+2.5E-1*tt1**2)
END
SUBROUTINE &
&stvk_elas_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = F(3,1)**2+F(2,1)**2+F(1,1)**2-1
tt2 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt4 = F(3,2)**2+F(2,2)**2+F(1,2)**2-1
tt5 = F(3,3)**2+F(2,3)**2+F(1,3)**2-1
tt6 = 5.0E-1*tt5+5.0E-1*tt4+5.0E-1*tt1
tt7 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
jac(1,1) = 1.0E+0*F(1,1)*lam(1,1)*tt6+mu(1,1)*(1.0E+0*F(1,3)*tt3+&
&1.0E+0*F(1,2)*tt2+1.0E+0*F(1,1)*tt1)
jac(1,2) = 1.0E+0*lam(1,1)*F(2,1)*tt6+mu(1,1)*(1.0E+0*F(2,3)*tt3+&
&1.0E+0*F(2,2)*tt2+1.0E+0*F(2,1)*tt1)
jac(1,3) = 1.0E+0*lam(1,1)*F(3,1)*tt6+mu(1,1)*(1.0E+0*F(3,3)*tt3+&
&1.0E+0*F(3,2)*tt2+1.0E+0*F(3,1)*tt1)
jac(1,4) = 1.0E+0*lam(1,1)*F(1,2)*tt6+mu(1,1)*(1.0E+0*F(1,3)*tt7+&
&1.0E+0*F(1,2)*tt4+1.0E+0*F(1,1)*tt2)
jac(1,5) = 1.0E+0*lam(1,1)*F(2,2)*tt6+mu(1,1)*(1.0E+0*F(2,3)*tt7+&
&1.0E+0*F(2,2)*tt4+1.0E+0*F(2,1)*tt2)
jac(1,6) = 1.0E+0*lam(1,1)*F(3,2)*tt6+mu(1,1)*(1.0E+0*F(3,3)*tt7+&
&1.0E+0*F(3,2)*tt4+1.0E+0*F(3,1)*tt2)
jac(1,7) = mu(1,1)*(1.0E+0*F(1,3)*tt5+1.0E+0*F(1,2)*tt7+1.0E+0*F(&
&1,1)*tt3)+1.0E+0*lam(1,1)*F(1,3)*tt6
jac(1,8) = mu(1,1)*(1.0E+0*F(2,3)*tt5+1.0E+0*F(2,2)*tt7+1.0E+0*F(&
&2,1)*tt3)+1.0E+0*lam(1,1)*F(2,3)*tt6
jac(1,9) = mu(1,1)*(1.0E+0*F(3,3)*tt5+1.0E+0*F(3,2)*tt7+1.0E+0*F(&
&3,1)*tt3)+1.0E+0*lam(1,1)*F(3,3)*tt6
END
SUBROUTINE &
&stvk_elas_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
REAL(KIND=8)  tt64
REAL(KIND=8)  tt65
REAL(KIND=8)  tt66
REAL(KIND=8)  tt67
REAL(KIND=8)  tt68
REAL(KIND=8)  tt69
REAL(KIND=8)  tt70
REAL(KIND=8)  tt71
REAL(KIND=8)  tt72
REAL(KIND=8)  tt73
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = 1.0E+0*tt2
tt4 = F(1,3)**2
tt5 = 1.0E+0*tt4
tt6 = F(2,1)**2
tt7 = F(3,1)**2
tt8 = tt7+tt6+tt1-1
tt9 = 1.0E+0*tt8
tt10 = F(2,2)**2
tt11 = F(3,2)**2
tt12 = tt11+tt10+tt2-1
tt13 = F(2,3)**2
tt14 = F(3,3)**2
tt15 = tt14+tt13+tt4-1
tt16 = 1.0E+0*lam(1,1)*(5.0E-1*tt15+5.0E-1*tt12+5.0E-1*tt8)
tt17 = 1.0E+0*F(1,2)*F(2,2)
tt18 = 1.0E+0*F(1,3)*F(2,3)
tt19 = mu(1,1)*(tt18+tt17+2.0E+0*F(1,1)*F(2,1))+1.0E+0*F(1,1)*lam&
&(1,1)*F(2,1)
tt20 = 1.0E+0*F(1,2)*F(3,2)
tt21 = 1.0E+0*F(1,3)*F(3,3)
tt22 = mu(1,1)*(tt21+tt20+2.0E+0*F(1,1)*F(3,1))+1.0E+0*F(1,1)*lam&
&(1,1)*F(3,1)
tt23 = 1.0E+0*(F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt24 = mu(1,1)*(tt23+1.0E+0*F(1,1)*F(1,2))+1.0E+0*F(1,1)*lam(1,1)&
&*F(1,2)
tt25 = 1.0E+0*F(1,1)*lam(1,1)*F(2,2)+1.0E+0*mu(1,1)*F(1,2)*F(2,1)&
&
tt26 = 1.0E+0*F(1,1)*lam(1,1)*F(3,2)+1.0E+0*mu(1,1)*F(1,2)*F(3,1)&
&
tt27 = 1.0E+0*(F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3))
tt28 = mu(1,1)*(tt27+1.0E+0*F(1,1)*F(1,3))+1.0E+0*F(1,1)*lam(1,1)&
&*F(1,3)
tt29 = 1.0E+0*F(1,1)*lam(1,1)*F(2,3)+1.0E+0*mu(1,1)*F(1,3)*F(2,1)&
&
tt30 = 1.0E+0*F(1,1)*lam(1,1)*F(3,3)+1.0E+0*mu(1,1)*F(1,3)*F(3,1)&
&
tt31 = 1.0E+0*tt10
tt32 = 1.0E+0*tt13
tt33 = 1.0E+0*F(2,2)*F(3,2)
tt34 = 1.0E+0*F(2,3)*F(3,3)
tt35 = mu(1,1)*(tt34+tt33+2.0E+0*F(2,1)*F(3,1))+1.0E+0*lam(1,1)*F&
&(2,1)*F(3,1)
tt36 = 1.0E+0*F(1,1)*mu(1,1)*F(2,2)+1.0E+0*lam(1,1)*F(1,2)*F(2,1)&
&
tt37 = mu(1,1)*(tt23+1.0E+0*F(2,1)*F(2,2))+1.0E+0*lam(1,1)*F(2,1)&
&*F(2,2)
tt38 = 1.0E+0*lam(1,1)*F(2,1)*F(3,2)+1.0E+0*mu(1,1)*F(2,2)*F(3,1)&
&
tt39 = 1.0E+0*F(1,1)*mu(1,1)*F(2,3)+1.0E+0*lam(1,1)*F(1,3)*F(2,1)&
&
tt40 = mu(1,1)*(tt27+1.0E+0*F(2,1)*F(2,3))+1.0E+0*lam(1,1)*F(2,1)&
&*F(2,3)
tt41 = 1.0E+0*lam(1,1)*F(2,1)*F(3,3)+1.0E+0*mu(1,1)*F(2,3)*F(3,1)&
&
tt42 = 1.0E+0*tt11
tt43 = 1.0E+0*tt14
tt44 = 1.0E+0*F(1,1)*mu(1,1)*F(3,2)+1.0E+0*lam(1,1)*F(1,2)*F(3,1)&
&
tt45 = 1.0E+0*mu(1,1)*F(2,1)*F(3,2)+1.0E+0*lam(1,1)*F(2,2)*F(3,1)&
&
tt46 = mu(1,1)*(tt23+1.0E+0*F(3,1)*F(3,2))+1.0E+0*lam(1,1)*F(3,1)&
&*F(3,2)
tt47 = 1.0E+0*F(1,1)*mu(1,1)*F(3,3)+1.0E+0*lam(1,1)*F(1,3)*F(3,1)&
&
tt48 = 1.0E+0*mu(1,1)*F(2,1)*F(3,3)+1.0E+0*lam(1,1)*F(2,3)*F(3,1)&
&
tt49 = mu(1,1)*(tt27+1.0E+0*F(3,1)*F(3,3))+1.0E+0*lam(1,1)*F(3,1)&
&*F(3,3)
tt50 = 1.0E+0*tt1
tt51 = 1.0E+0*tt12
tt52 = 1.0E+0*F(1,1)*F(2,1)
tt53 = mu(1,1)*(tt18+2.0E+0*F(1,2)*F(2,2)+tt52)+1.0E+0*lam(1,1)*F&
&(1,2)*F(2,2)
tt54 = 1.0E+0*F(1,1)*F(3,1)
tt55 = mu(1,1)*(tt21+2.0E+0*F(1,2)*F(3,2)+tt54)+1.0E+0*lam(1,1)*F&
&(1,2)*F(3,2)
tt56 = 1.0E+0*(F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3))
tt57 = mu(1,1)*(tt56+1.0E+0*F(1,2)*F(1,3))+1.0E+0*lam(1,1)*F(1,2)&
&*F(1,3)
tt58 = 1.0E+0*lam(1,1)*F(1,2)*F(2,3)+1.0E+0*mu(1,1)*F(1,3)*F(2,2)&
&
tt59 = 1.0E+0*lam(1,1)*F(1,2)*F(3,3)+1.0E+0*mu(1,1)*F(1,3)*F(3,2)&
&
tt60 = 1.0E+0*tt6
tt61 = 1.0E+0*F(2,1)*F(3,1)
tt62 = mu(1,1)*(tt34+2.0E+0*F(2,2)*F(3,2)+tt61)+1.0E+0*lam(1,1)*F&
&(2,2)*F(3,2)
tt63 = 1.0E+0*mu(1,1)*F(1,2)*F(2,3)+1.0E+0*lam(1,1)*F(1,3)*F(2,2)&
&
tt64 = mu(1,1)*(tt56+1.0E+0*F(2,2)*F(2,3))+1.0E+0*lam(1,1)*F(2,2)&
&*F(2,3)
tt65 = 1.0E+0*lam(1,1)*F(2,2)*F(3,3)+1.0E+0*mu(1,1)*F(2,3)*F(3,2)&
&
tt66 = 1.0E+0*tt7
tt67 = 1.0E+0*mu(1,1)*F(1,2)*F(3,3)+1.0E+0*lam(1,1)*F(1,3)*F(3,2)&
&
tt68 = 1.0E+0*mu(1,1)*F(2,2)*F(3,3)+1.0E+0*lam(1,1)*F(2,3)*F(3,2)&
&
tt69 = mu(1,1)*(tt56+1.0E+0*F(3,2)*F(3,3))+1.0E+0*lam(1,1)*F(3,2)&
&*F(3,3)
tt70 = 1.0E+0*tt15
tt71 = mu(1,1)*(2.0E+0*F(1,3)*F(2,3)+tt17+tt52)+1.0E+0*lam(1,1)*F&
&(1,3)*F(2,3)
tt72 = mu(1,1)*(2.0E+0*F(1,3)*F(3,3)+tt20+tt54)+1.0E+0*lam(1,1)*F&
&(1,3)*F(3,3)
tt73 = mu(1,1)*(2.0E+0*F(2,3)*F(3,3)+tt33+tt61)+1.0E+0*lam(1,1)*F&
&(2,3)*F(3,3)
hes(1,1) = tt16+mu(1,1)*(tt9+tt5+tt3+2.0E+0*tt1)+1.0E+0*tt1*lam(1&
&,1)
hes(1,2) = tt19
hes(1,3) = tt22
hes(1,4) = tt24
hes(1,5) = tt25
hes(1,6) = tt26
hes(1,7) = tt28
hes(1,8) = tt29
hes(1,9) = tt30
hes(2,1) = tt19
hes(2,2) = tt16+mu(1,1)*(tt9+tt32+tt31+2.0E+0*tt6)+1.0E+0*lam(1,1&
&)*tt6
hes(2,3) = tt35
hes(2,4) = tt36
hes(2,5) = tt37
hes(2,6) = tt38
hes(2,7) = tt39
hes(2,8) = tt40
hes(2,9) = tt41
hes(3,1) = tt22
hes(3,2) = tt35
hes(3,3) = tt16+mu(1,1)*(tt43+tt42+tt9+2.0E+0*tt7)+1.0E+0*lam(1,1&
&)*tt7
hes(3,4) = tt44
hes(3,5) = tt45
hes(3,6) = tt46
hes(3,7) = tt47
hes(3,8) = tt48
hes(3,9) = tt49
hes(4,1) = tt24
hes(4,2) = tt36
hes(4,3) = tt44
hes(4,4) = tt16+mu(1,1)*(tt51+tt5+2.0E+0*tt2+tt50)+1.0E+0*lam(1,1&
&)*tt2
hes(4,5) = tt53
hes(4,6) = tt55
hes(4,7) = tt57
hes(4,8) = tt58
hes(4,9) = tt59
hes(5,1) = tt25
hes(5,2) = tt37
hes(5,3) = tt45
hes(5,4) = tt53
hes(5,5) = tt16+mu(1,1)*(tt51+tt32+2.0E+0*tt10+tt60)+1.0E+0*lam(1&
&,1)*tt10
hes(5,6) = tt62
hes(5,7) = tt63
hes(5,8) = tt64
hes(5,9) = tt65
hes(6,1) = tt26
hes(6,2) = tt38
hes(6,3) = tt46
hes(6,4) = tt55
hes(6,5) = tt62
hes(6,6) = tt16+mu(1,1)*(tt43+tt51+2.0E+0*tt11+tt66)+1.0E+0*lam(1&
&,1)*tt11
hes(6,7) = tt67
hes(6,8) = tt68
hes(6,9) = tt69
hes(7,1) = tt28
hes(7,2) = tt39
hes(7,3) = tt47
hes(7,4) = tt57
hes(7,5) = tt63
hes(7,6) = tt67
hes(7,7) = mu(1,1)*(tt70+2.0E+0*tt4+tt3+tt50)+tt16+1.0E+0*lam(1,1&
&)*tt4
hes(7,8) = tt71
hes(7,9) = tt72
hes(8,1) = tt29
hes(8,2) = tt40
hes(8,3) = tt48
hes(8,4) = tt58
hes(8,5) = tt64
hes(8,6) = tt68
hes(8,7) = tt71
hes(8,8) = mu(1,1)*(tt70+2.0E+0*tt13+tt31+tt60)+tt16+1.0E+0*lam(1&
&,1)*tt13
hes(8,9) = tt73
hes(9,1) = tt30
hes(9,2) = tt41
hes(9,3) = tt49
hes(9,4) = tt59
hes(9,5) = tt65
hes(9,6) = tt69
hes(9,7) = tt72
hes(9,8) = tt73
hes(9,9) = mu(1,1)*(tt70+2.0E+0*tt14+tt42+tt66)+tt16+1.0E+0*lam(1&
&,1)*tt14
END
SUBROUTINE &
&coro_elas_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
val(1,1) = 5.0E-1*lam(1,1)*(5.0E-1*(2*F(3,3)*R(3,3)+2*F(2,3)*R(2,&
&3)+2*F(1,3)*R(1,3))+5.0E-1*(2*F(3,2)*R(3,2)+2*F(2,2)*R(2,2)+2*F(1&
&,2)*R(1,2))+5.0E-1*(2*F(3,1)*R(3,1)+2*F(2,1)*R(2,1)+2*F(1,1)*R(1,&
&1))-3)**2+mu(1,1)*((1.0E+0*F(3,3)*R(3,3)+1.0E+0*F(2,3)*R(2,3)+1.0&
&E+0*F(1,3)*R(1,3)-1)**2+5.0E-1*(F(3,2)*R(3,3)+R(3,2)*F(3,3)+F(2,2&
&)*R(2,3)+R(2,2)*F(2,3)+F(1,2)*R(1,3)+R(1,2)*F(1,3))**2+5.0E-1*(F(&
&3,1)*R(3,3)+R(3,1)*F(3,3)+F(2,1)*R(2,3)+R(2,1)*F(2,3)+F(1,1)*R(1,&
&3)+R(1,1)*F(1,3))**2+(1.0E+0*F(3,2)*R(3,2)+1.0E+0*F(2,2)*R(2,2)+1&
&.0E+0*F(1,2)*R(1,2)-1)**2+5.0E-1*(F(3,1)*R(3,2)+R(3,1)*F(3,2)+F(2&
&,1)*R(2,2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2))**2+(1.0E+0*&
&F(3,1)*R(3,1)+1.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1,1)-1)**2)
END
SUBROUTINE &
&coro_elas_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
tt1 = 1.0E+0*F(3,1)*R(3,1)+1.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1&
&,1)-1
tt2 = F(3,1)*R(3,2)+R(3,1)*F(3,2)+F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1&
&,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = F(3,1)*R(3,3)+R(3,1)*F(3,3)+F(2,1)*R(2,3)+R(2,1)*F(2,3)+F(1&
&,1)*R(1,3)+R(1,1)*F(1,3)
tt4 = 5.0E-1*(2*F(3,3)*R(3,3)+2*F(2,3)*R(2,3)+2*F(1,3)*R(1,3))+5.&
&0E-1*(2*F(3,2)*R(3,2)+2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))+5.0E-1*(2*&
&F(3,1)*R(3,1)+2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-3
tt5 = 1.0E+0*F(3,2)*R(3,2)+1.0E+0*F(2,2)*R(2,2)+1.0E+0*F(1,2)*R(1&
&,2)-1
tt6 = F(3,2)*R(3,3)+R(3,2)*F(3,3)+F(2,2)*R(2,3)+R(2,2)*F(2,3)+F(1&
&,2)*R(1,3)+R(1,2)*F(1,3)
tt7 = 1.0E+0*F(3,3)*R(3,3)+1.0E+0*F(2,3)*R(2,3)+1.0E+0*F(1,3)*R(1&
&,3)-1
jac(1,1) = 1.0E+0*R(1,1)*lam(1,1)*tt4+mu(1,1)*(1.0E+0*R(1,3)*tt3+&
&1.0E+0*R(1,2)*tt2+2.0E+0*R(1,1)*tt1)
jac(1,2) = 1.0E+0*lam(1,1)*R(2,1)*tt4+mu(1,1)*(1.0E+0*R(2,3)*tt3+&
&1.0E+0*R(2,2)*tt2+2.0E+0*R(2,1)*tt1)
jac(1,3) = 1.0E+0*lam(1,1)*R(3,1)*tt4+mu(1,1)*(1.0E+0*R(3,3)*tt3+&
&1.0E+0*R(3,2)*tt2+2.0E+0*R(3,1)*tt1)
jac(1,4) = 1.0E+0*lam(1,1)*R(1,2)*tt4+mu(1,1)*(1.0E+0*R(1,3)*tt6+&
&2.0E+0*R(1,2)*tt5+1.0E+0*R(1,1)*tt2)
jac(1,5) = 1.0E+0*lam(1,1)*R(2,2)*tt4+mu(1,1)*(1.0E+0*R(2,3)*tt6+&
&2.0E+0*R(2,2)*tt5+1.0E+0*R(2,1)*tt2)
jac(1,6) = 1.0E+0*lam(1,1)*R(3,2)*tt4+mu(1,1)*(1.0E+0*R(3,3)*tt6+&
&2.0E+0*R(3,2)*tt5+1.0E+0*R(3,1)*tt2)
jac(1,7) = 1.0E+0*lam(1,1)*R(1,3)*tt4+mu(1,1)*(2.0E+0*R(1,3)*tt7+&
&1.0E+0*R(1,2)*tt6+1.0E+0*R(1,1)*tt3)
jac(1,8) = 1.0E+0*lam(1,1)*R(2,3)*tt4+mu(1,1)*(2.0E+0*R(2,3)*tt7+&
&1.0E+0*R(2,2)*tt6+1.0E+0*R(2,1)*tt3)
jac(1,9) = 1.0E+0*lam(1,1)*R(3,3)*tt4+mu(1,1)*(2.0E+0*R(3,3)*tt7+&
&1.0E+0*R(3,2)*tt6+1.0E+0*R(3,1)*tt3)
END
SUBROUTINE &
&coro_elas_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
tt1 = R(1,1)**2
tt2 = R(1,2)**2
tt3 = 1.0E+0*tt2
tt4 = R(1,3)**2
tt5 = 1.0E+0*tt4
tt6 = 1.0E+0*R(1,2)*R(2,2)
tt7 = 1.0E+0*R(1,3)*R(2,3)
tt8 = mu(1,1)*(tt7+tt6+2.0E+0*R(1,1)*R(2,1))+1.0E+0*R(1,1)*lam(1,&
&1)*R(2,1)
tt9 = 1.0E+0*R(1,2)*R(3,2)
tt10 = 1.0E+0*R(1,3)*R(3,3)
tt11 = mu(1,1)*(tt10+tt9+2.0E+0*R(1,1)*R(3,1))+1.0E+0*R(1,1)*lam(&
&1,1)*R(3,1)
tt12 = 1.0E+0*R(1,1)*mu(1,1)*R(1,2)+1.0E+0*R(1,1)*lam(1,1)*R(1,2)&
&
tt13 = 1.0E+0*R(1,1)*lam(1,1)*R(2,2)+1.0E+0*mu(1,1)*R(1,2)*R(2,1)&
&
tt14 = 1.0E+0*R(1,1)*lam(1,1)*R(3,2)+1.0E+0*mu(1,1)*R(1,2)*R(3,1)&
&
tt15 = 1.0E+0*R(1,1)*mu(1,1)*R(1,3)+1.0E+0*R(1,1)*lam(1,1)*R(1,3)&
&
tt16 = 1.0E+0*R(1,1)*lam(1,1)*R(2,3)+1.0E+0*mu(1,1)*R(1,3)*R(2,1)&
&
tt17 = 1.0E+0*R(1,1)*lam(1,1)*R(3,3)+1.0E+0*mu(1,1)*R(1,3)*R(3,1)&
&
tt18 = R(2,1)**2
tt19 = R(2,2)**2
tt20 = 1.0E+0*tt19
tt21 = R(2,3)**2
tt22 = 1.0E+0*tt21
tt23 = 1.0E+0*R(2,2)*R(3,2)
tt24 = 1.0E+0*R(2,3)*R(3,3)
tt25 = mu(1,1)*(tt24+tt23+2.0E+0*R(2,1)*R(3,1))+1.0E+0*lam(1,1)*R&
&(2,1)*R(3,1)
tt26 = 1.0E+0*R(1,1)*mu(1,1)*R(2,2)+1.0E+0*lam(1,1)*R(1,2)*R(2,1)&
&
tt27 = 1.0E+0*mu(1,1)*R(2,1)*R(2,2)+1.0E+0*lam(1,1)*R(2,1)*R(2,2)&
&
tt28 = 1.0E+0*lam(1,1)*R(2,1)*R(3,2)+1.0E+0*mu(1,1)*R(2,2)*R(3,1)&
&
tt29 = 1.0E+0*R(1,1)*mu(1,1)*R(2,3)+1.0E+0*lam(1,1)*R(1,3)*R(2,1)&
&
tt30 = 1.0E+0*mu(1,1)*R(2,1)*R(2,3)+1.0E+0*lam(1,1)*R(2,1)*R(2,3)&
&
tt31 = 1.0E+0*lam(1,1)*R(2,1)*R(3,3)+1.0E+0*mu(1,1)*R(2,3)*R(3,1)&
&
tt32 = R(3,1)**2
tt33 = R(3,2)**2
tt34 = 1.0E+0*tt33
tt35 = R(3,3)**2
tt36 = 1.0E+0*tt35
tt37 = 1.0E+0*R(1,1)*mu(1,1)*R(3,2)+1.0E+0*lam(1,1)*R(1,2)*R(3,1)&
&
tt38 = 1.0E+0*mu(1,1)*R(2,1)*R(3,2)+1.0E+0*lam(1,1)*R(2,2)*R(3,1)&
&
tt39 = 1.0E+0*mu(1,1)*R(3,1)*R(3,2)+1.0E+0*lam(1,1)*R(3,1)*R(3,2)&
&
tt40 = 1.0E+0*R(1,1)*mu(1,1)*R(3,3)+1.0E+0*lam(1,1)*R(1,3)*R(3,1)&
&
tt41 = 1.0E+0*mu(1,1)*R(2,1)*R(3,3)+1.0E+0*lam(1,1)*R(2,3)*R(3,1)&
&
tt42 = 1.0E+0*mu(1,1)*R(3,1)*R(3,3)+1.0E+0*lam(1,1)*R(3,1)*R(3,3)&
&
tt43 = 1.0E+0*tt1
tt44 = 1.0E+0*R(1,1)*R(2,1)
tt45 = mu(1,1)*(tt7+2.0E+0*R(1,2)*R(2,2)+tt44)+1.0E+0*lam(1,1)*R(&
&1,2)*R(2,2)
tt46 = 1.0E+0*R(1,1)*R(3,1)
tt47 = mu(1,1)*(tt10+2.0E+0*R(1,2)*R(3,2)+tt46)+1.0E+0*lam(1,1)*R&
&(1,2)*R(3,2)
tt48 = 1.0E+0*mu(1,1)*R(1,2)*R(1,3)+1.0E+0*lam(1,1)*R(1,2)*R(1,3)&
&
tt49 = 1.0E+0*lam(1,1)*R(1,2)*R(2,3)+1.0E+0*mu(1,1)*R(1,3)*R(2,2)&
&
tt50 = 1.0E+0*lam(1,1)*R(1,2)*R(3,3)+1.0E+0*mu(1,1)*R(1,3)*R(3,2)&
&
tt51 = 1.0E+0*tt18
tt52 = 1.0E+0*R(2,1)*R(3,1)
tt53 = mu(1,1)*(tt24+2.0E+0*R(2,2)*R(3,2)+tt52)+1.0E+0*lam(1,1)*R&
&(2,2)*R(3,2)
tt54 = 1.0E+0*mu(1,1)*R(1,2)*R(2,3)+1.0E+0*lam(1,1)*R(1,3)*R(2,2)&
&
tt55 = 1.0E+0*mu(1,1)*R(2,2)*R(2,3)+1.0E+0*lam(1,1)*R(2,2)*R(2,3)&
&
tt56 = 1.0E+0*lam(1,1)*R(2,2)*R(3,3)+1.0E+0*mu(1,1)*R(2,3)*R(3,2)&
&
tt57 = 1.0E+0*tt32
tt58 = 1.0E+0*mu(1,1)*R(1,2)*R(3,3)+1.0E+0*lam(1,1)*R(1,3)*R(3,2)&
&
tt59 = 1.0E+0*mu(1,1)*R(2,2)*R(3,3)+1.0E+0*lam(1,1)*R(2,3)*R(3,2)&
&
tt60 = 1.0E+0*mu(1,1)*R(3,2)*R(3,3)+1.0E+0*lam(1,1)*R(3,2)*R(3,3)&
&
tt61 = mu(1,1)*(2.0E+0*R(1,3)*R(2,3)+tt6+tt44)+1.0E+0*lam(1,1)*R(&
&1,3)*R(2,3)
tt62 = mu(1,1)*(2.0E+0*R(1,3)*R(3,3)+tt9+tt46)+1.0E+0*lam(1,1)*R(&
&1,3)*R(3,3)
tt63 = mu(1,1)*(2.0E+0*R(2,3)*R(3,3)+tt23+tt52)+1.0E+0*lam(1,1)*R&
&(2,3)*R(3,3)
hes(1,1) = mu(1,1)*(tt5+tt3+2.0E+0*tt1)+1.0E+0*tt1*lam(1,1)
hes(1,2) = tt8
hes(1,3) = tt11
hes(1,4) = tt12
hes(1,5) = tt13
hes(1,6) = tt14
hes(1,7) = tt15
hes(1,8) = tt16
hes(1,9) = tt17
hes(2,1) = tt8
hes(2,2) = mu(1,1)*(tt22+tt20+2.0E+0*tt18)+1.0E+0*lam(1,1)*tt18
hes(2,3) = tt25
hes(2,4) = tt26
hes(2,5) = tt27
hes(2,6) = tt28
hes(2,7) = tt29
hes(2,8) = tt30
hes(2,9) = tt31
hes(3,1) = tt11
hes(3,2) = tt25
hes(3,3) = mu(1,1)*(tt36+tt34+2.0E+0*tt32)+1.0E+0*lam(1,1)*tt32
hes(3,4) = tt37
hes(3,5) = tt38
hes(3,6) = tt39
hes(3,7) = tt40
hes(3,8) = tt41
hes(3,9) = tt42
hes(4,1) = tt12
hes(4,2) = tt26
hes(4,3) = tt37
hes(4,4) = mu(1,1)*(tt5+2.0E+0*tt2+tt43)+1.0E+0*lam(1,1)*tt2
hes(4,5) = tt45
hes(4,6) = tt47
hes(4,7) = tt48
hes(4,8) = tt49
hes(4,9) = tt50
hes(5,1) = tt13
hes(5,2) = tt27
hes(5,3) = tt38
hes(5,4) = tt45
hes(5,5) = mu(1,1)*(tt22+2.0E+0*tt19+tt51)+1.0E+0*lam(1,1)*tt19
hes(5,6) = tt53
hes(5,7) = tt54
hes(5,8) = tt55
hes(5,9) = tt56
hes(6,1) = tt14
hes(6,2) = tt28
hes(6,3) = tt39
hes(6,4) = tt47
hes(6,5) = tt53
hes(6,6) = mu(1,1)*(tt36+2.0E+0*tt33+tt57)+1.0E+0*lam(1,1)*tt33
hes(6,7) = tt58
hes(6,8) = tt59
hes(6,9) = tt60
hes(7,1) = tt15
hes(7,2) = tt29
hes(7,3) = tt40
hes(7,4) = tt48
hes(7,5) = tt54
hes(7,6) = tt58
hes(7,7) = mu(1,1)*(2.0E+0*tt4+tt3+tt43)+1.0E+0*lam(1,1)*tt4
hes(7,8) = tt61
hes(7,9) = tt62
hes(8,1) = tt16
hes(8,2) = tt30
hes(8,3) = tt41
hes(8,4) = tt49
hes(8,5) = tt55
hes(8,6) = tt59
hes(8,7) = tt61
hes(8,8) = mu(1,1)*(2.0E+0*tt21+tt20+tt51)+1.0E+0*lam(1,1)*tt21
hes(8,9) = tt63
hes(9,1) = tt17
hes(9,2) = tt31
hes(9,3) = tt42
hes(9,4) = tt50
hes(9,5) = tt56
hes(9,6) = tt60
hes(9,7) = tt62
hes(9,8) = tt63
hes(9,9) = mu(1,1)*(2.0E+0*tt35+tt34+tt57)+1.0E+0*lam(1,1)*tt35
END
SUBROUTINE &
&mcadams_coro_elas_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
val(1,1) = mu(1,1)*((R(3,3)-F(3,3))**2+(R(3,2)-F(3,2))**2+(R(3,1)&
&-F(3,1))**2+(R(2,3)-F(2,3))**2+(R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))&
&**2+(R(1,3)-F(1,3))**2+(R(1,2)-F(1,2))**2+(R(1,1)-F(1,1))**2)+5.0&
&E-1*lam(1,1)*((-R(3,3))+F(3,3)-R(2,2)+F(2,2)-R(1,1)+F(1,1))**2
END
SUBROUTINE &
&mcadams_coro_elas_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*lam(1,1)*((-R(3,3))+F(3,3)-R(2,2)+F(2,2)-R(1,1)+F(1,&
&1))
jac(1,1) = tt1-2*(R(1,1)-F(1,1))*mu(1,1)
jac(1,2) = -2*mu(1,1)*(R(2,1)-F(2,1))
jac(1,3) = -2*mu(1,1)*(R(3,1)-F(3,1))
jac(1,4) = -2*mu(1,1)*(R(1,2)-F(1,2))
jac(1,5) = tt1-2*mu(1,1)*(R(2,2)-F(2,2))
jac(1,6) = -2*mu(1,1)*(R(3,2)-F(3,2))
jac(1,7) = -2*mu(1,1)*(R(1,3)-F(1,3))
jac(1,8) = -2*mu(1,1)*(R(2,3)-F(2,3))
jac(1,9) = tt1-2*mu(1,1)*(R(3,3)-F(3,3))
END
SUBROUTINE &
&mcadams_coro_elas_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 1.0E+0*lam(1,1)
tt2 = 2*mu(1,1)
tt3 = tt2+tt1
hes(1,1) = tt3
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = tt1
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = tt1
hes(2,1) = 0
hes(2,2) = tt2
hes(2,3) = 0
hes(2,4) = 0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = tt2
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = tt2
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = tt1
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = tt3
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = tt1
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = tt2
hes(6,7) = 0
hes(6,8) = 0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = tt2
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 0
hes(8,7) = 0
hes(8,8) = tt2
hes(8,9) = 0
hes(9,1) = tt1
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = tt1
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = tt3
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
val(1,1) = mu(1,1)*((R(3,3)-F(3,3))**2+(R(3,2)-F(3,2))**2+(R(3,1)&
&-F(3,1))**2+(R(2,3)-F(2,3))**2+(R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))&
&**2+(R(1,3)-F(1,3))**2+(R(1,2)-F(1,2))**2+(R(1,1)-F(1,1))**2)+5.0&
&E-1*lam(1,1)*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F(2,1)&
&*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-1)**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
jac(1,1) = 1.0E+0*lam(1,1)*tt1*tt3-2*(R(1,1)-F(1,1))*mu(1,1)
jac(1,2) = 1.0E+0*lam(1,1)*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3-2*mu&
&(1,1)*(R(2,1)-F(2,1))
jac(1,3) = 1.0E+0*lam(1,1)*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3-2*mu&
&(1,1)*(R(3,1)-F(3,1))
jac(1,4) = 1.0E+0*lam(1,1)*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3-2*mu&
&(1,1)*(R(1,2)-F(1,2))
jac(1,5) = 1.0E+0*lam(1,1)*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3-2*mu&
&(1,1)*(R(2,2)-F(2,2))
jac(1,6) = 1.0E+0*lam(1,1)*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3-2*mu&
&(1,1)*(R(3,2)-F(3,2))
jac(1,7) = 1.0E+0*lam(1,1)*tt2*tt3-2*mu(1,1)*(R(1,3)-F(1,3))
jac(1,8) = 1.0E+0*lam(1,1)*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3-2*mu&
&(1,1)*(R(2,3)-F(2,3))
jac(1,9) = 1.0E+0*lam(1,1)*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3-2*mu&
&(1,1)*(R(3,3)-F(3,3))
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8) R(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
tt1 = 2*mu(1,1)
tt2 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt3 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt4 = 1.0E+0*lam(1,1)*tt3*tt2
tt5 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt6 = 1.0E+0*lam(1,1)*tt5*tt2
tt7 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt8 = 1.0E+0*lam(1,1)*tt7*tt2
tt9 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt10 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt11 = F(1,1)*tt2-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt1&
&0-1
tt12 = 1.0E+0*lam(1,1)*F(3,3)*tt11+1.0E+0*lam(1,1)*tt9*tt2
tt13 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt14 = 1.0E+0*lam(1,1)*tt13*tt2-1.0E+0*lam(1,1)*F(2,3)*tt11
tt15 = 1.0E+0*lam(1,1)*tt10*tt2
tt16 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt17 = 1.0E+0*lam(1,1)*tt16*tt2-1.0E+0*lam(1,1)*F(3,2)*tt11
tt18 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt19 = 1.0E+0*lam(1,1)*F(2,2)*tt11+1.0E+0*lam(1,1)*tt18*tt2
tt20 = 1.0E+0*lam(1,1)*tt5*tt3
tt21 = 1.0E+0*lam(1,1)*tt3*tt7-1.0E+0*lam(1,1)*F(3,3)*tt11
tt22 = 1.0E+0*lam(1,1)*tt9*tt3
tt23 = 1.0E+0*lam(1,1)*F(1,3)*tt11+1.0E+0*lam(1,1)*tt13*tt3
tt24 = 1.0E+0*lam(1,1)*F(3,2)*tt11+1.0E+0*lam(1,1)*tt10*tt3
tt25 = 1.0E+0*lam(1,1)*tt16*tt3
tt26 = 1.0E+0*lam(1,1)*tt18*tt3-1.0E+0*lam(1,1)*F(1,2)*tt11
tt27 = 1.0E+0*lam(1,1)*F(2,3)*tt11+1.0E+0*lam(1,1)*tt5*tt7
tt28 = 1.0E+0*lam(1,1)*tt5*tt9-1.0E+0*lam(1,1)*F(1,3)*tt11
tt29 = 1.0E+0*lam(1,1)*tt13*tt5
tt30 = 1.0E+0*lam(1,1)*tt5*tt10-1.0E+0*lam(1,1)*F(2,2)*tt11
tt31 = 1.0E+0*lam(1,1)*F(1,2)*tt11+1.0E+0*lam(1,1)*tt5*tt16
tt32 = 1.0E+0*lam(1,1)*tt18*tt5
tt33 = 1.0E+0*lam(1,1)*tt9*tt7
tt34 = 1.0E+0*lam(1,1)*tt13*tt7
tt35 = 1.0E+0*lam(1,1)*tt10*tt7
tt36 = 1.0E+0*lam(1,1)*F(3,1)*tt11+1.0E+0*lam(1,1)*tt16*tt7
tt37 = 1.0E+0*lam(1,1)*tt18*tt7-1.0E+0*lam(1,1)*F(2,1)*tt11
tt38 = 1.0E+0*lam(1,1)*tt13*tt9
tt39 = 1.0E+0*lam(1,1)*tt10*tt9-1.0E+0*lam(1,1)*F(3,1)*tt11
tt40 = 1.0E+0*lam(1,1)*tt16*tt9
tt41 = 1.0E+0*F(1,1)*lam(1,1)*tt11+1.0E+0*lam(1,1)*tt18*tt9
tt42 = 1.0E+0*lam(1,1)*F(2,1)*tt11+1.0E+0*lam(1,1)*tt13*tt10
tt43 = 1.0E+0*lam(1,1)*tt13*tt16-1.0E+0*F(1,1)*lam(1,1)*tt11
tt44 = 1.0E+0*lam(1,1)*tt18*tt13
tt45 = 1.0E+0*lam(1,1)*tt16*tt10
tt46 = 1.0E+0*lam(1,1)*tt18*tt10
tt47 = 1.0E+0*lam(1,1)*tt18*tt16
hes(1,1) = 1.0E+0*lam(1,1)*tt2**2+tt1
hes(1,2) = tt4
hes(1,3) = tt6
hes(1,4) = tt8
hes(1,5) = tt12
hes(1,6) = tt14
hes(1,7) = tt15
hes(1,8) = tt17
hes(1,9) = tt19
hes(2,1) = tt4
hes(2,2) = 1.0E+0*lam(1,1)*tt3**2+tt1
hes(2,3) = tt20
hes(2,4) = tt21
hes(2,5) = tt22
hes(2,6) = tt23
hes(2,7) = tt24
hes(2,8) = tt25
hes(2,9) = tt26
hes(3,1) = tt6
hes(3,2) = tt20
hes(3,3) = 1.0E+0*lam(1,1)*tt5**2+tt1
hes(3,4) = tt27
hes(3,5) = tt28
hes(3,6) = tt29
hes(3,7) = tt30
hes(3,8) = tt31
hes(3,9) = tt32
hes(4,1) = tt8
hes(4,2) = tt21
hes(4,3) = tt27
hes(4,4) = 1.0E+0*lam(1,1)*tt7**2+tt1
hes(4,5) = tt33
hes(4,6) = tt34
hes(4,7) = tt35
hes(4,8) = tt36
hes(4,9) = tt37
hes(5,1) = tt12
hes(5,2) = tt22
hes(5,3) = tt28
hes(5,4) = tt33
hes(5,5) = 1.0E+0*lam(1,1)*tt9**2+tt1
hes(5,6) = tt38
hes(5,7) = tt39
hes(5,8) = tt40
hes(5,9) = tt41
hes(6,1) = tt14
hes(6,2) = tt23
hes(6,3) = tt29
hes(6,4) = tt34
hes(6,5) = tt38
hes(6,6) = 1.0E+0*lam(1,1)*tt13**2+tt1
hes(6,7) = tt42
hes(6,8) = tt43
hes(6,9) = tt44
hes(7,1) = tt15
hes(7,2) = tt24
hes(7,3) = tt30
hes(7,4) = tt35
hes(7,5) = tt39
hes(7,6) = tt42
hes(7,7) = 1.0E+0*lam(1,1)*tt10**2+tt1
hes(7,8) = tt45
hes(7,9) = tt46
hes(8,1) = tt17
hes(8,2) = tt25
hes(8,3) = tt31
hes(8,4) = tt36
hes(8,5) = tt40
hes(8,6) = tt43
hes(8,7) = tt45
hes(8,8) = 1.0E+0*lam(1,1)*tt16**2+tt1
hes(8,9) = tt47
hes(9,1) = tt19
hes(9,2) = tt26
hes(9,3) = tt32
hes(9,4) = tt37
hes(9,5) = tt41
hes(9,6) = tt44
hes(9,7) = tt46
hes(9,8) = tt47
hes(9,9) = 1.0E+0*lam(1,1)*tt18**2+tt1
END
SUBROUTINE &
&bonet08_neohookean_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
tt1 = log(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F(2,1)*F(3&
&,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1)))
val(1,1) = 5.0E-1*lam(1,1)*tt1**2-mu(1,1)*tt1+5.0E-1*mu(1,1)*(F(3&
&,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2+F(1,3)**&
&2+F(1,2)**2+F(1,1)**2-3)
END
SUBROUTINE &
&bonet08_neohookean_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2
tt4 = 1/tt3
tt5 = log(tt3)
tt6 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt7 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt8 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt9 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt10 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt11 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt12 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
jac(1,1) = 1.0E+0*lam(1,1)*tt1*tt4*tt5-mu(1,1)*tt1*tt4+1.0E+0*F(1&
&,1)*mu(1,1)
jac(1,2) = 1.0E+0*lam(1,1)*tt6*tt4*tt5-mu(1,1)*tt6*tt4+1.0E+0*mu(&
&1,1)*F(2,1)
jac(1,3) = 1.0E+0*lam(1,1)*tt7*tt4*tt5-mu(1,1)*tt7*tt4+1.0E+0*mu(&
&1,1)*F(3,1)
jac(1,4) = 1.0E+0*lam(1,1)*tt8*tt4*tt5-mu(1,1)*tt8*tt4+1.0E+0*mu(&
&1,1)*F(1,2)
jac(1,5) = 1.0E+0*lam(1,1)*tt9*tt4*tt5-mu(1,1)*tt9*tt4+1.0E+0*mu(&
&1,1)*F(2,2)
jac(1,6) = 1.0E+0*lam(1,1)*tt10*tt4*tt5-mu(1,1)*tt10*tt4+1.0E+0*m&
&u(1,1)*F(3,2)
jac(1,7) = 1.0E+0*lam(1,1)*tt2*tt4*tt5-mu(1,1)*tt2*tt4+1.0E+0*mu(&
&1,1)*F(1,3)
jac(1,8) = 1.0E+0*lam(1,1)*tt11*tt4*tt5-mu(1,1)*tt11*tt4+1.0E+0*m&
&u(1,1)*F(2,3)
jac(1,9) = 1.0E+0*lam(1,1)*tt12*tt4*tt5-mu(1,1)*tt12*tt4+1.0E+0*m&
&u(1,1)*F(3,3)
END
SUBROUTINE &
&bonet08_neohookean_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
tt1 = 1.0E+0*mu(1,1)
tt2 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt3 = tt2**2
tt4 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt5 = F(1,1)*tt2-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt4
tt6 = 1/tt5**2
tt7 = log(tt5)
tt8 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt9 = (-1.0E+0*lam(1,1)*tt8*tt2*tt6*tt7)+mu(1,1)*tt8*tt2*tt6+1.0E&
&+0*lam(1,1)*tt8*tt2*tt6
tt10 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt11 = (-1.0E+0*lam(1,1)*tt10*tt2*tt6*tt7)+mu(1,1)*tt10*tt2*tt6+1&
&.0E+0*lam(1,1)*tt10*tt2*tt6
tt12 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt13 = (-1.0E+0*lam(1,1)*tt12*tt2*tt6*tt7)+mu(1,1)*tt12*tt2*tt6+1&
&.0E+0*lam(1,1)*tt12*tt2*tt6
tt14 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt15 = 1/tt5
tt16 = 1.0E+0*lam(1,1)*F(3,3)*tt15*tt7-1.0E+0*lam(1,1)*tt14*tt2*t&
&t6*tt7-mu(1,1)*F(3,3)*tt15+mu(1,1)*tt14*tt2*tt6+1.0E+0*lam(1,1)*t&
&t14*tt2*tt6
tt17 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt18 = (-1.0E+0*lam(1,1)*F(2,3)*tt15*tt7)-1.0E+0*lam(1,1)*tt17*tt&
&2*tt6*tt7+mu(1,1)*F(2,3)*tt15+mu(1,1)*tt17*tt2*tt6+1.0E+0*lam(1,1&
&)*tt17*tt2*tt6
tt19 = (-1.0E+0*lam(1,1)*tt4*tt2*tt6*tt7)+mu(1,1)*tt4*tt2*tt6+1.0&
&E+0*lam(1,1)*tt4*tt2*tt6
tt20 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt21 = (-1.0E+0*lam(1,1)*F(3,2)*tt15*tt7)-1.0E+0*lam(1,1)*tt20*tt&
&2*tt6*tt7+mu(1,1)*F(3,2)*tt15+mu(1,1)*tt20*tt2*tt6+1.0E+0*lam(1,1&
&)*tt20*tt2*tt6
tt22 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt23 = 1.0E+0*lam(1,1)*F(2,2)*tt15*tt7-1.0E+0*lam(1,1)*tt22*tt2*t&
&t6*tt7-mu(1,1)*F(2,2)*tt15+mu(1,1)*tt22*tt2*tt6+1.0E+0*lam(1,1)*t&
&t22*tt2*tt6
tt24 = tt8**2
tt25 = (-1.0E+0*lam(1,1)*tt10*tt8*tt6*tt7)+mu(1,1)*tt10*tt8*tt6+1&
&.0E+0*lam(1,1)*tt10*tt8*tt6
tt26 = (-1.0E+0*lam(1,1)*F(3,3)*tt15*tt7)-1.0E+0*lam(1,1)*tt8*tt1&
&2*tt6*tt7+mu(1,1)*F(3,3)*tt15+mu(1,1)*tt8*tt12*tt6+1.0E+0*lam(1,1&
&)*tt8*tt12*tt6
tt27 = (-1.0E+0*lam(1,1)*tt14*tt8*tt6*tt7)+mu(1,1)*tt14*tt8*tt6+1&
&.0E+0*lam(1,1)*tt14*tt8*tt6
tt28 = 1.0E+0*lam(1,1)*F(1,3)*tt15*tt7-1.0E+0*lam(1,1)*tt17*tt8*t&
&t6*tt7-mu(1,1)*F(1,3)*tt15+mu(1,1)*tt17*tt8*tt6+1.0E+0*lam(1,1)*t&
&t17*tt8*tt6
tt29 = 1.0E+0*lam(1,1)*F(3,2)*tt15*tt7-1.0E+0*lam(1,1)*tt4*tt8*tt&
&6*tt7-mu(1,1)*F(3,2)*tt15+mu(1,1)*tt4*tt8*tt6+1.0E+0*lam(1,1)*tt4&
&*tt8*tt6
tt30 = (-1.0E+0*lam(1,1)*tt20*tt8*tt6*tt7)+mu(1,1)*tt20*tt8*tt6+1&
&.0E+0*lam(1,1)*tt20*tt8*tt6
tt31 = (-1.0E+0*lam(1,1)*F(1,2)*tt15*tt7)-1.0E+0*lam(1,1)*tt22*tt&
&8*tt6*tt7+mu(1,1)*F(1,2)*tt15+mu(1,1)*tt22*tt8*tt6+1.0E+0*lam(1,1&
&)*tt22*tt8*tt6
tt32 = tt10**2
tt33 = 1.0E+0*lam(1,1)*F(2,3)*tt15*tt7-1.0E+0*lam(1,1)*tt10*tt12*&
&tt6*tt7-mu(1,1)*F(2,3)*tt15+mu(1,1)*tt10*tt12*tt6+1.0E+0*lam(1,1)&
&*tt10*tt12*tt6
tt34 = (-1.0E+0*lam(1,1)*F(1,3)*tt15*tt7)-1.0E+0*lam(1,1)*tt10*tt&
&14*tt6*tt7+mu(1,1)*F(1,3)*tt15+mu(1,1)*tt10*tt14*tt6+1.0E+0*lam(1&
&,1)*tt10*tt14*tt6
tt35 = (-1.0E+0*lam(1,1)*tt17*tt10*tt6*tt7)+mu(1,1)*tt17*tt10*tt6&
&+1.0E+0*lam(1,1)*tt17*tt10*tt6
tt36 = (-1.0E+0*lam(1,1)*F(2,2)*tt15*tt7)-1.0E+0*lam(1,1)*tt10*tt&
&4*tt6*tt7+mu(1,1)*F(2,2)*tt15+mu(1,1)*tt10*tt4*tt6+1.0E+0*lam(1,1&
&)*tt10*tt4*tt6
tt37 = 1.0E+0*lam(1,1)*F(1,2)*tt15*tt7-1.0E+0*lam(1,1)*tt10*tt20*&
&tt6*tt7-mu(1,1)*F(1,2)*tt15+mu(1,1)*tt10*tt20*tt6+1.0E+0*lam(1,1)&
&*tt10*tt20*tt6
tt38 = (-1.0E+0*lam(1,1)*tt22*tt10*tt6*tt7)+mu(1,1)*tt22*tt10*tt6&
&+1.0E+0*lam(1,1)*tt22*tt10*tt6
tt39 = tt12**2
tt40 = (-1.0E+0*lam(1,1)*tt14*tt12*tt6*tt7)+mu(1,1)*tt14*tt12*tt6&
&+1.0E+0*lam(1,1)*tt14*tt12*tt6
tt41 = (-1.0E+0*lam(1,1)*tt17*tt12*tt6*tt7)+mu(1,1)*tt17*tt12*tt6&
&+1.0E+0*lam(1,1)*tt17*tt12*tt6
tt42 = (-1.0E+0*lam(1,1)*tt4*tt12*tt6*tt7)+mu(1,1)*tt4*tt12*tt6+1&
&.0E+0*lam(1,1)*tt4*tt12*tt6
tt43 = 1.0E+0*lam(1,1)*F(3,1)*tt15*tt7-1.0E+0*lam(1,1)*tt20*tt12*&
&tt6*tt7-mu(1,1)*F(3,1)*tt15+mu(1,1)*tt20*tt12*tt6+1.0E+0*lam(1,1)&
&*tt20*tt12*tt6
tt44 = (-1.0E+0*lam(1,1)*F(2,1)*tt15*tt7)-1.0E+0*lam(1,1)*tt22*tt&
&12*tt6*tt7+mu(1,1)*F(2,1)*tt15+mu(1,1)*tt22*tt12*tt6+1.0E+0*lam(1&
&,1)*tt22*tt12*tt6
tt45 = tt14**2
tt46 = (-1.0E+0*lam(1,1)*tt17*tt14*tt6*tt7)+mu(1,1)*tt17*tt14*tt6&
&+1.0E+0*lam(1,1)*tt17*tt14*tt6
tt47 = (-1.0E+0*lam(1,1)*F(3,1)*tt15*tt7)-1.0E+0*lam(1,1)*tt4*tt1&
&4*tt6*tt7+mu(1,1)*F(3,1)*tt15+mu(1,1)*tt4*tt14*tt6+1.0E+0*lam(1,1&
&)*tt4*tt14*tt6
tt48 = (-1.0E+0*lam(1,1)*tt20*tt14*tt6*tt7)+mu(1,1)*tt20*tt14*tt6&
&+1.0E+0*lam(1,1)*tt20*tt14*tt6
tt49 = 1.0E+0*F(1,1)*lam(1,1)*tt15*tt7-1.0E+0*lam(1,1)*tt22*tt14*&
&tt6*tt7-F(1,1)*mu(1,1)*tt15+mu(1,1)*tt22*tt14*tt6+1.0E+0*lam(1,1)&
&*tt22*tt14*tt6
tt50 = tt17**2
tt51 = 1.0E+0*lam(1,1)*F(2,1)*tt15*tt7-1.0E+0*lam(1,1)*tt17*tt4*t&
&t6*tt7-mu(1,1)*F(2,1)*tt15+mu(1,1)*tt17*tt4*tt6+1.0E+0*lam(1,1)*t&
&t17*tt4*tt6
tt52 = (-1.0E+0*F(1,1)*lam(1,1)*tt15*tt7)-1.0E+0*lam(1,1)*tt17*tt&
&20*tt6*tt7+F(1,1)*mu(1,1)*tt15+mu(1,1)*tt17*tt20*tt6+1.0E+0*lam(1&
&,1)*tt17*tt20*tt6
tt53 = (-1.0E+0*lam(1,1)*tt22*tt17*tt6*tt7)+mu(1,1)*tt22*tt17*tt6&
&+1.0E+0*lam(1,1)*tt22*tt17*tt6
tt54 = tt4**2
tt55 = (-1.0E+0*lam(1,1)*tt20*tt4*tt6*tt7)+mu(1,1)*tt20*tt4*tt6+1&
&.0E+0*lam(1,1)*tt20*tt4*tt6
tt56 = (-1.0E+0*lam(1,1)*tt22*tt4*tt6*tt7)+mu(1,1)*tt22*tt4*tt6+1&
&.0E+0*lam(1,1)*tt22*tt4*tt6
tt57 = tt20**2
tt58 = (-1.0E+0*lam(1,1)*tt22*tt20*tt6*tt7)+mu(1,1)*tt22*tt20*tt6&
&+1.0E+0*lam(1,1)*tt22*tt20*tt6
tt59 = tt22**2
hes(1,1) = (-1.0E+0*lam(1,1)*tt3*tt6*tt7)+mu(1,1)*tt3*tt6+1.0E+0*&
&lam(1,1)*tt3*tt6+tt1
hes(1,2) = tt9
hes(1,3) = tt11
hes(1,4) = tt13
hes(1,5) = tt16
hes(1,6) = tt18
hes(1,7) = tt19
hes(1,8) = tt21
hes(1,9) = tt23
hes(2,1) = tt9
hes(2,2) = (-1.0E+0*lam(1,1)*tt24*tt6*tt7)+mu(1,1)*tt24*tt6+1.0E+&
&0*lam(1,1)*tt24*tt6+tt1
hes(2,3) = tt25
hes(2,4) = tt26
hes(2,5) = tt27
hes(2,6) = tt28
hes(2,7) = tt29
hes(2,8) = tt30
hes(2,9) = tt31
hes(3,1) = tt11
hes(3,2) = tt25
hes(3,3) = (-1.0E+0*lam(1,1)*tt32*tt6*tt7)+mu(1,1)*tt32*tt6+1.0E+&
&0*lam(1,1)*tt32*tt6+tt1
hes(3,4) = tt33
hes(3,5) = tt34
hes(3,6) = tt35
hes(3,7) = tt36
hes(3,8) = tt37
hes(3,9) = tt38
hes(4,1) = tt13
hes(4,2) = tt26
hes(4,3) = tt33
hes(4,4) = (-1.0E+0*lam(1,1)*tt39*tt6*tt7)+mu(1,1)*tt39*tt6+1.0E+&
&0*lam(1,1)*tt39*tt6+tt1
hes(4,5) = tt40
hes(4,6) = tt41
hes(4,7) = tt42
hes(4,8) = tt43
hes(4,9) = tt44
hes(5,1) = tt16
hes(5,2) = tt27
hes(5,3) = tt34
hes(5,4) = tt40
hes(5,5) = (-1.0E+0*lam(1,1)*tt45*tt6*tt7)+mu(1,1)*tt45*tt6+1.0E+&
&0*lam(1,1)*tt45*tt6+tt1
hes(5,6) = tt46
hes(5,7) = tt47
hes(5,8) = tt48
hes(5,9) = tt49
hes(6,1) = tt18
hes(6,2) = tt28
hes(6,3) = tt35
hes(6,4) = tt41
hes(6,5) = tt46
hes(6,6) = (-1.0E+0*lam(1,1)*tt50*tt6*tt7)+mu(1,1)*tt50*tt6+1.0E+&
&0*lam(1,1)*tt50*tt6+tt1
hes(6,7) = tt51
hes(6,8) = tt52
hes(6,9) = tt53
hes(7,1) = tt19
hes(7,2) = tt29
hes(7,3) = tt36
hes(7,4) = tt42
hes(7,5) = tt47
hes(7,6) = tt51
hes(7,7) = (-1.0E+0*lam(1,1)*tt54*tt6*tt7)+mu(1,1)*tt54*tt6+1.0E+&
&0*lam(1,1)*tt54*tt6+tt1
hes(7,8) = tt55
hes(7,9) = tt56
hes(8,1) = tt21
hes(8,2) = tt30
hes(8,3) = tt37
hes(8,4) = tt43
hes(8,5) = tt48
hes(8,6) = tt52
hes(8,7) = tt55
hes(8,8) = (-1.0E+0*lam(1,1)*tt57*tt6*tt7)+mu(1,1)*tt57*tt6+1.0E+&
&0*lam(1,1)*tt57*tt6+tt1
hes(8,9) = tt58
hes(9,1) = tt23
hes(9,2) = tt31
hes(9,3) = tt38
hes(9,4) = tt44
hes(9,5) = tt49
hes(9,6) = tt53
hes(9,7) = tt56
hes(9,8) = tt58
hes(9,9) = (-1.0E+0*lam(1,1)*tt59*tt6*tt7)+mu(1,1)*tt59*tt6+1.0E+&
&0*lam(1,1)*tt59*tt6+tt1
END
SUBROUTINE &
&ogden97_neohookean_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))
tt2 = -F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))
tt3 = F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))
val(1,1) = (-mu(1,1)*log(tt3+tt2+tt1))+5.0E-1*lam(1,1)*(tt3+tt2+t&
&t1-1)**2+5.0E-1*mu(1,1)*(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+&
&F(2,2)**2+F(2,1)**2+F(1,3)**2+F(1,2)**2+F(1,1)**2-3)
END
SUBROUTINE &
&ogden97_neohookean_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,3)*tt2
tt4 = -F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))
tt5 = F(1,1)*tt1
tt6 = tt5+tt4+tt3-1
tt7 = 1/(tt5+tt4+tt3)
tt8 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt9 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt10 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt11 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt12 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt13 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt14 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
jac(1,1) = (-mu(1,1)*tt1*tt7)+1.0E+0*lam(1,1)*tt1*tt6+1.0E+0*F(1,&
&1)*mu(1,1)
jac(1,2) = (-mu(1,1)*tt8*tt7)+1.0E+0*lam(1,1)*tt8*tt6+1.0E+0*mu(1&
&,1)*F(2,1)
jac(1,3) = (-mu(1,1)*tt9*tt7)+1.0E+0*lam(1,1)*tt9*tt6+1.0E+0*mu(1&
&,1)*F(3,1)
jac(1,4) = (-mu(1,1)*tt10*tt7)+1.0E+0*lam(1,1)*tt10*tt6+1.0E+0*mu&
&(1,1)*F(1,2)
jac(1,5) = (-mu(1,1)*tt11*tt7)+1.0E+0*lam(1,1)*tt11*tt6+1.0E+0*mu&
&(1,1)*F(2,2)
jac(1,6) = (-mu(1,1)*tt12*tt7)+1.0E+0*lam(1,1)*tt12*tt6+1.0E+0*mu&
&(1,1)*F(3,2)
jac(1,7) = (-mu(1,1)*tt2*tt7)+1.0E+0*lam(1,1)*tt2*tt6+1.0E+0*mu(1&
&,1)*F(1,3)
jac(1,8) = (-mu(1,1)*tt13*tt7)+1.0E+0*lam(1,1)*tt13*tt6+1.0E+0*mu&
&(1,1)*F(2,3)
jac(1,9) = (-mu(1,1)*tt14*tt7)+1.0E+0*lam(1,1)*tt14*tt6+1.0E+0*mu&
&(1,1)*F(3,3)
END
SUBROUTINE &
&ogden97_neohookean_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
tt1 = 1.0E+0*mu(1,1)
tt2 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt3 = tt2**2
tt4 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt5 = F(1,3)*tt4
tt6 = -F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))
tt7 = F(1,1)*tt2
tt8 = tt7+tt6+tt5
tt9 = 1/tt8**2
tt10 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt11 = mu(1,1)*tt10*tt2*tt9+1.0E+0*lam(1,1)*tt10*tt2
tt12 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt13 = mu(1,1)*tt12*tt2*tt9+1.0E+0*lam(1,1)*tt12*tt2
tt14 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt15 = mu(1,1)*tt14*tt2*tt9+1.0E+0*lam(1,1)*tt14*tt2
tt16 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt17 = tt7+tt6+tt5-1
tt18 = 1/tt8
tt19 = (-mu(1,1)*F(3,3)*tt18)+mu(1,1)*tt16*tt2*tt9+1.0E+0*lam(1,1&
&)*F(3,3)*tt17+1.0E+0*lam(1,1)*tt16*tt2
tt20 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt21 = mu(1,1)*F(2,3)*tt18+mu(1,1)*tt20*tt2*tt9-1.0E+0*lam(1,1)*F&
&(2,3)*tt17+1.0E+0*lam(1,1)*tt20*tt2
tt22 = mu(1,1)*tt4*tt2*tt9+1.0E+0*lam(1,1)*tt4*tt2
tt23 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt24 = mu(1,1)*F(3,2)*tt18+mu(1,1)*tt23*tt2*tt9-1.0E+0*lam(1,1)*F&
&(3,2)*tt17+1.0E+0*lam(1,1)*tt23*tt2
tt25 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt26 = (-mu(1,1)*F(2,2)*tt18)+mu(1,1)*tt25*tt2*tt9+1.0E+0*lam(1,1&
&)*F(2,2)*tt17+1.0E+0*lam(1,1)*tt25*tt2
tt27 = tt10**2
tt28 = mu(1,1)*tt12*tt10*tt9+1.0E+0*lam(1,1)*tt12*tt10
tt29 = mu(1,1)*F(3,3)*tt18+mu(1,1)*tt10*tt14*tt9-1.0E+0*lam(1,1)*&
&F(3,3)*tt17+1.0E+0*lam(1,1)*tt10*tt14
tt30 = mu(1,1)*tt16*tt10*tt9+1.0E+0*lam(1,1)*tt16*tt10
tt31 = (-mu(1,1)*F(1,3)*tt18)+mu(1,1)*tt20*tt10*tt9+1.0E+0*lam(1,&
&1)*F(1,3)*tt17+1.0E+0*lam(1,1)*tt20*tt10
tt32 = (-mu(1,1)*F(3,2)*tt18)+mu(1,1)*tt4*tt10*tt9+1.0E+0*lam(1,1&
&)*F(3,2)*tt17+1.0E+0*lam(1,1)*tt4*tt10
tt33 = mu(1,1)*tt23*tt10*tt9+1.0E+0*lam(1,1)*tt23*tt10
tt34 = mu(1,1)*F(1,2)*tt18+mu(1,1)*tt25*tt10*tt9-1.0E+0*lam(1,1)*&
&F(1,2)*tt17+1.0E+0*lam(1,1)*tt25*tt10
tt35 = tt12**2
tt36 = (-mu(1,1)*F(2,3)*tt18)+mu(1,1)*tt12*tt14*tt9+1.0E+0*lam(1,&
&1)*F(2,3)*tt17+1.0E+0*lam(1,1)*tt12*tt14
tt37 = mu(1,1)*F(1,3)*tt18+mu(1,1)*tt12*tt16*tt9-1.0E+0*lam(1,1)*&
&F(1,3)*tt17+1.0E+0*lam(1,1)*tt12*tt16
tt38 = mu(1,1)*tt20*tt12*tt9+1.0E+0*lam(1,1)*tt20*tt12
tt39 = mu(1,1)*F(2,2)*tt18+mu(1,1)*tt12*tt4*tt9-1.0E+0*lam(1,1)*F&
&(2,2)*tt17+1.0E+0*lam(1,1)*tt12*tt4
tt40 = (-mu(1,1)*F(1,2)*tt18)+mu(1,1)*tt12*tt23*tt9+1.0E+0*lam(1,&
&1)*F(1,2)*tt17+1.0E+0*lam(1,1)*tt12*tt23
tt41 = mu(1,1)*tt25*tt12*tt9+1.0E+0*lam(1,1)*tt25*tt12
tt42 = tt14**2
tt43 = mu(1,1)*tt16*tt14*tt9+1.0E+0*lam(1,1)*tt16*tt14
tt44 = mu(1,1)*tt20*tt14*tt9+1.0E+0*lam(1,1)*tt20*tt14
tt45 = mu(1,1)*tt4*tt14*tt9+1.0E+0*lam(1,1)*tt4*tt14
tt46 = (-mu(1,1)*F(3,1)*tt18)+mu(1,1)*tt23*tt14*tt9+1.0E+0*lam(1,&
&1)*F(3,1)*tt17+1.0E+0*lam(1,1)*tt23*tt14
tt47 = mu(1,1)*F(2,1)*tt18+mu(1,1)*tt25*tt14*tt9-1.0E+0*lam(1,1)*&
&F(2,1)*tt17+1.0E+0*lam(1,1)*tt25*tt14
tt48 = tt16**2
tt49 = mu(1,1)*tt20*tt16*tt9+1.0E+0*lam(1,1)*tt20*tt16
tt50 = mu(1,1)*F(3,1)*tt18+mu(1,1)*tt4*tt16*tt9-1.0E+0*lam(1,1)*F&
&(3,1)*tt17+1.0E+0*lam(1,1)*tt4*tt16
tt51 = mu(1,1)*tt23*tt16*tt9+1.0E+0*lam(1,1)*tt23*tt16
tt52 = (-F(1,1)*mu(1,1)*tt18)+mu(1,1)*tt25*tt16*tt9+1.0E+0*F(1,1)&
&*lam(1,1)*tt17+1.0E+0*lam(1,1)*tt25*tt16
tt53 = tt20**2
tt54 = (-mu(1,1)*F(2,1)*tt18)+mu(1,1)*tt20*tt4*tt9+1.0E+0*lam(1,1&
&)*F(2,1)*tt17+1.0E+0*lam(1,1)*tt20*tt4
tt55 = F(1,1)*mu(1,1)*tt18+mu(1,1)*tt20*tt23*tt9-1.0E+0*F(1,1)*la&
&m(1,1)*tt17+1.0E+0*lam(1,1)*tt20*tt23
tt56 = mu(1,1)*tt25*tt20*tt9+1.0E+0*lam(1,1)*tt25*tt20
tt57 = tt4**2
tt58 = mu(1,1)*tt23*tt4*tt9+1.0E+0*lam(1,1)*tt23*tt4
tt59 = mu(1,1)*tt25*tt4*tt9+1.0E+0*lam(1,1)*tt25*tt4
tt60 = tt23**2
tt61 = mu(1,1)*tt25*tt23*tt9+1.0E+0*lam(1,1)*tt25*tt23
tt62 = tt25**2
hes(1,1) = mu(1,1)*tt3*tt9+1.0E+0*lam(1,1)*tt3+tt1
hes(1,2) = tt11
hes(1,3) = tt13
hes(1,4) = tt15
hes(1,5) = tt19
hes(1,6) = tt21
hes(1,7) = tt22
hes(1,8) = tt24
hes(1,9) = tt26
hes(2,1) = tt11
hes(2,2) = mu(1,1)*tt27*tt9+1.0E+0*lam(1,1)*tt27+tt1
hes(2,3) = tt28
hes(2,4) = tt29
hes(2,5) = tt30
hes(2,6) = tt31
hes(2,7) = tt32
hes(2,8) = tt33
hes(2,9) = tt34
hes(3,1) = tt13
hes(3,2) = tt28
hes(3,3) = mu(1,1)*tt35*tt9+1.0E+0*lam(1,1)*tt35+tt1
hes(3,4) = tt36
hes(3,5) = tt37
hes(3,6) = tt38
hes(3,7) = tt39
hes(3,8) = tt40
hes(3,9) = tt41
hes(4,1) = tt15
hes(4,2) = tt29
hes(4,3) = tt36
hes(4,4) = mu(1,1)*tt42*tt9+1.0E+0*lam(1,1)*tt42+tt1
hes(4,5) = tt43
hes(4,6) = tt44
hes(4,7) = tt45
hes(4,8) = tt46
hes(4,9) = tt47
hes(5,1) = tt19
hes(5,2) = tt30
hes(5,3) = tt37
hes(5,4) = tt43
hes(5,5) = mu(1,1)*tt48*tt9+1.0E+0*lam(1,1)*tt48+tt1
hes(5,6) = tt49
hes(5,7) = tt50
hes(5,8) = tt51
hes(5,9) = tt52
hes(6,1) = tt21
hes(6,2) = tt31
hes(6,3) = tt38
hes(6,4) = tt44
hes(6,5) = tt49
hes(6,6) = mu(1,1)*tt53*tt9+1.0E+0*lam(1,1)*tt53+tt1
hes(6,7) = tt54
hes(6,8) = tt55
hes(6,9) = tt56
hes(7,1) = tt22
hes(7,2) = tt32
hes(7,3) = tt39
hes(7,4) = tt45
hes(7,5) = tt50
hes(7,6) = tt54
hes(7,7) = mu(1,1)*tt57*tt9+1.0E+0*lam(1,1)*tt57+tt1
hes(7,8) = tt58
hes(7,9) = tt59
hes(8,1) = tt24
hes(8,2) = tt33
hes(8,3) = tt40
hes(8,4) = tt46
hes(8,5) = tt51
hes(8,6) = tt55
hes(8,7) = tt58
hes(8,8) = mu(1,1)*tt60*tt9+1.0E+0*lam(1,1)*tt60+tt1
hes(8,9) = tt61
hes(9,1) = tt26
hes(9,2) = tt34
hes(9,3) = tt41
hes(9,4) = tt47
hes(9,5) = tt52
hes(9,6) = tt56
hes(9,7) = tt59
hes(9,8) = tt61
hes(9,9) = mu(1,1)*tt62*tt9+1.0E+0*lam(1,1)*tt62+tt1
END
SUBROUTINE &
&bower09_neohookean_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))
tt2 = -F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))
tt3 = F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))
val(1,1) = 5.0E-1*lam(1,1)*(tt3+tt2+tt1-1)**2+5.0E-1*mu(1,1)*((F(&
&3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2+F(1,3)*&
&*2+F(1,2)**2+F(1,1)**2)/(tt3+tt2+tt1)**(2.0E+0/3.0E+0)-3)
END
SUBROUTINE &
&bower09_neohookean_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,3)*tt2
tt4 = -F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))
tt5 = F(1,1)*tt1
tt6 = tt5+tt4+tt3-1
tt7 = tt5+tt4+tt3
tt8 = tt7**((-5.0E+0)/3.0E+0)
tt9 = F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2&
&+F(1,3)**2+F(1,2)**2+F(1,1)**2
tt10 = tt7**((-2.0E+0)/3.0E+0)
tt11 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt12 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt13 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt14 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt15 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt16 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt17 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
jac(1,1) = 5.0E-1*mu(1,1)*(2*F(1,1)*tt10+((-2.0E+0)*tt1*tt8*tt9)/&
&3.0E+0)+1.0E+0*lam(1,1)*tt1*tt6
jac(1,2) = 5.0E-1*mu(1,1)*(2*F(2,1)*tt10+((-2.0E+0)*tt11*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt11*tt6
jac(1,3) = 5.0E-1*mu(1,1)*(2*F(3,1)*tt10+((-2.0E+0)*tt12*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt12*tt6
jac(1,4) = 5.0E-1*mu(1,1)*(2*F(1,2)*tt10+((-2.0E+0)*tt13*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt13*tt6
jac(1,5) = 5.0E-1*mu(1,1)*(2*F(2,2)*tt10+((-2.0E+0)*tt14*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt14*tt6
jac(1,6) = 5.0E-1*mu(1,1)*(2*F(3,2)*tt10+((-2.0E+0)*tt15*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt15*tt6
jac(1,7) = 5.0E-1*mu(1,1)*(2*F(1,3)*tt10+((-2.0E+0)*tt2*tt8*tt9)/&
&3.0E+0)+1.0E+0*lam(1,1)*tt2*tt6
jac(1,8) = 5.0E-1*mu(1,1)*(2*F(2,3)*tt10+((-2.0E+0)*tt16*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt16*tt6
jac(1,9) = 5.0E-1*mu(1,1)*(2*F(3,3)*tt10+((-2.0E+0)*tt17*tt8*tt9)&
&/3.0E+0)+1.0E+0*lam(1,1)*tt17*tt6
END
SUBROUTINE &
&bower09_neohookean_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = tt1**2
tt3 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt4 = F(1,3)*tt3
tt5 = -F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))
tt6 = F(1,1)*tt1
tt7 = tt6+tt5+tt4
tt8 = tt7**((-8.0E+0)/3.0E+0)
tt9 = F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2&
&+F(1,3)**2+F(1,2)**2+F(1,1)**2
tt10 = tt7**((-5.0E+0)/3.0E+0)
tt11 = 2/tt7**(2.0E+0/3.0E+0)
tt12 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt13 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,1)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt12*tt10)/3.0E+0+(1.0E+1*tt12*tt1*tt8*tt9)/9.0E+0)+1.&
&0E+0*lam(1,1)*tt12*tt1
tt14 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt15 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,1)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt14*tt10)/3.0E+0+(1.0E+1*tt14*tt1*tt8*tt9)/9.0E+0)+1.&
&0E+0*lam(1,1)*tt14*tt1
tt16 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt17 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(1,2)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt16*tt10)/3.0E+0+(1.0E+1*tt16*tt1*tt8*tt9)/9.0E+0)+1.&
&0E+0*lam(1,1)*tt16*tt1
tt18 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt19 = tt6+tt5+tt4-1
tt20 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,2)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt18*tt10)/3.0E+0+((-2.0E+0)*F(3,3)*tt10*tt9)/3.0E+0+(&
&1.0E+1*tt18*tt1*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(3,3)*tt19+1.0E&
&+0*lam(1,1)*tt18*tt1
tt21 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt22 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,2)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt21*tt10)/3.0E+0+(2.0E+0*F(2,3)*tt10*tt9)/3.0E+0+(1.0&
&E+1*tt21*tt1*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(2,3)*tt19+1.0E+0*&
&lam(1,1)*tt21*tt1
tt23 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(1,3)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt3*tt10)/3.0E+0+(1.0E+1*tt3*tt1*tt8*tt9)/9.0E+0)+1.0E&
&+0*lam(1,1)*tt3*tt1
tt24 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt25 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,3)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt24*tt10)/3.0E+0+(2.0E+0*F(3,2)*tt10*tt9)/3.0E+0+(1.0&
&E+1*tt24*tt1*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(3,2)*tt19+1.0E+0*&
&lam(1,1)*tt24*tt1
tt26 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt27 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,3)*tt1*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,1)*tt26*tt10)/3.0E+0+((-2.0E+0)*F(2,2)*tt10*tt9)/3.0E+0+(&
&1.0E+1*tt26*tt1*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(2,2)*tt19+1.0E&
&+0*lam(1,1)*tt26*tt1
tt28 = tt12**2
tt29 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,1)*tt12*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,1)*tt14*tt10)/3.0E+0+(1.0E+1*tt14*tt12*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt14*tt12
tt30 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,1)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt12*tt10)/3.0E+0+(2.0E+0*F(3,3)*tt10*tt9)/3.0E+0+(1.&
&0E+1*tt12*tt16*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(3,3)*tt19+1.0E+&
&0*lam(1,1)*tt12*tt16
tt31 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,2)*tt12*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,1)*tt18*tt10)/3.0E+0+(1.0E+1*tt18*tt12*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt18*tt12
tt32 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,2)*tt12*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,1)*tt21*tt10)/3.0E+0+((-2.0E+0)*F(1,3)*tt10*tt9)/3.0E+0+&
&(1.0E+1*tt21*tt12*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(1,3)*tt19+1.&
&0E+0*lam(1,1)*tt21*tt12
tt33 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(1,3)*tt12*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,1)*tt3*tt10)/3.0E+0+((-2.0E+0)*F(3,2)*tt10*tt9)/3.0E+0+(&
&1.0E+1*tt3*tt12*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(3,2)*tt19+1.0E&
&+0*lam(1,1)*tt3*tt12
tt34 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,3)*tt12*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,1)*tt24*tt10)/3.0E+0+(1.0E+1*tt24*tt12*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt24*tt12
tt35 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,3)*tt12*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,1)*tt26*tt10)/3.0E+0+(2.0E+0*F(1,2)*tt10*tt9)/3.0E+0+(1.&
&0E+1*tt26*tt12*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(1,2)*tt19+1.0E+&
&0*lam(1,1)*tt26*tt12
tt36 = tt14**2
tt37 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,1)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt14*tt10)/3.0E+0+((-2.0E+0)*F(2,3)*tt10*tt9)/3.0E+0+&
&(1.0E+1*tt14*tt16*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(2,3)*tt19+1.&
&0E+0*lam(1,1)*tt14*tt16
tt38 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,1)*tt18*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,2)*tt14*tt10)/3.0E+0+(2.0E+0*F(1,3)*tt10*tt9)/3.0E+0+(1.&
&0E+1*tt14*tt18*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(1,3)*tt19+1.0E+&
&0*lam(1,1)*tt14*tt18
tt39 = 5.0E-1*mu(1,1)*(((-4.0E+0)*tt14*F(3,2)*tt10)/3.0E+0+((-4.0&
&E+0)*tt21*F(3,1)*tt10)/3.0E+0+(1.0E+1*tt21*tt14*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt21*tt14
tt40 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,1)*tt3*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,3)*tt14*tt10)/3.0E+0+(2.0E+0*F(2,2)*tt10*tt9)/3.0E+0+(1.0&
&E+1*tt14*tt3*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(2,2)*tt19+1.0E+0*&
&lam(1,1)*tt14*tt3
tt41 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,1)*tt24*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,3)*tt14*tt10)/3.0E+0+((-2.0E+0)*F(1,2)*tt10*tt9)/3.0E+0+&
&(1.0E+1*tt14*tt24*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(1,2)*tt19+1.&
&0E+0*lam(1,1)*tt14*tt24
tt42 = 5.0E-1*mu(1,1)*(((-4.0E+0)*tt14*F(3,3)*tt10)/3.0E+0+((-4.0&
&E+0)*tt26*F(3,1)*tt10)/3.0E+0+(1.0E+1*tt26*tt14*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt26*tt14
tt43 = tt16**2
tt44 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,2)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt18*tt10)/3.0E+0+(1.0E+1*tt18*tt16*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt18*tt16
tt45 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,2)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt21*tt10)/3.0E+0+(1.0E+1*tt21*tt16*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt21*tt16
tt46 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(1,3)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt3*tt10)/3.0E+0+(1.0E+1*tt3*tt16*tt8*tt9)/9.0E+0)+1.&
&0E+0*lam(1,1)*tt3*tt16
tt47 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,3)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt24*tt10)/3.0E+0+((-2.0E+0)*F(3,1)*tt10*tt9)/3.0E+0+&
&(1.0E+1*tt24*tt16*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(3,1)*tt19+1.&
&0E+0*lam(1,1)*tt24*tt16
tt48 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,3)*tt16*tt10)/3.0E+0+((-4.0&
&E+0)*F(1,2)*tt26*tt10)/3.0E+0+(2.0E+0*F(2,1)*tt10*tt9)/3.0E+0+(1.&
&0E+1*tt26*tt16*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(2,1)*tt19+1.0E+&
&0*lam(1,1)*tt26*tt16
tt49 = tt18**2
tt50 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,2)*tt18*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,2)*tt21*tt10)/3.0E+0+(1.0E+1*tt21*tt18*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt21*tt18
tt51 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(1,3)*tt18*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,2)*tt3*tt10)/3.0E+0+(2.0E+0*F(3,1)*tt10*tt9)/3.0E+0+(1.0&
&E+1*tt3*tt18*tt8*tt9)/9.0E+0)-1.0E+0*lam(1,1)*F(3,1)*tt19+1.0E+0*&
&lam(1,1)*tt3*tt18
tt52 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,3)*tt18*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,2)*tt24*tt10)/3.0E+0+(1.0E+1*tt24*tt18*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt24*tt18
tt53 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,3)*tt18*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,2)*tt26*tt10)/3.0E+0+((-2.0E+0)*F(1,1)*tt10*tt9)/3.0E+0+&
&(1.0E+1*tt26*tt18*tt8*tt9)/9.0E+0)+1.0E+0*F(1,1)*lam(1,1)*tt19+1.&
&0E+0*lam(1,1)*tt26*tt18
tt54 = tt21**2
tt55 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,2)*tt3*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,3)*tt21*tt10)/3.0E+0+((-2.0E+0)*F(2,1)*tt10*tt9)/3.0E+0+(&
&1.0E+1*tt21*tt3*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*F(2,1)*tt19+1.0E&
&+0*lam(1,1)*tt21*tt3
tt56 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(3,2)*tt24*tt10)/3.0E+0+((-4.0&
&E+0)*F(2,3)*tt21*tt10)/3.0E+0+(2.0E+0*F(1,1)*tt10*tt9)/3.0E+0+(1.&
&0E+1*tt21*tt24*tt8*tt9)/9.0E+0)-1.0E+0*F(1,1)*lam(1,1)*tt19+1.0E+&
&0*lam(1,1)*tt21*tt24
tt57 = 5.0E-1*mu(1,1)*(((-4.0E+0)*tt21*F(3,3)*tt10)/3.0E+0+((-4.0&
&E+0)*tt26*F(3,2)*tt10)/3.0E+0+(1.0E+1*tt26*tt21*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt26*tt21
tt58 = tt3**2
tt59 = 5.0E-1*mu(1,1)*(((-4.0E+0)*F(2,3)*tt3*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,3)*tt24*tt10)/3.0E+0+(1.0E+1*tt24*tt3*tt8*tt9)/9.0E+0)+1.&
&0E+0*lam(1,1)*tt24*tt3
tt60 = 5.0E-1*mu(1,1)*(((-4.0E+0)*tt3*F(3,3)*tt10)/3.0E+0+((-4.0E&
&+0)*F(1,3)*tt26*tt10)/3.0E+0+(1.0E+1*tt26*tt3*tt8*tt9)/9.0E+0)+1.&
&0E+0*lam(1,1)*tt26*tt3
tt61 = tt24**2
tt62 = 5.0E-1*mu(1,1)*(((-4.0E+0)*tt24*F(3,3)*tt10)/3.0E+0+((-4.0&
&E+0)*tt26*F(2,3)*tt10)/3.0E+0+(1.0E+1*tt26*tt24*tt8*tt9)/9.0E+0)+&
&1.0E+0*lam(1,1)*tt26*tt24
tt63 = tt26**2
hes(1,1) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*F(1,1)*tt1*tt10)/3.0E+&
&0+(1.0E+1*tt2*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt2
hes(1,2) = tt13
hes(1,3) = tt15
hes(1,4) = tt17
hes(1,5) = tt20
hes(1,6) = tt22
hes(1,7) = tt23
hes(1,8) = tt25
hes(1,9) = tt27
hes(2,1) = tt13
hes(2,2) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*F(2,1)*tt12*tt10)/3.0E&
&+0+(1.0E+1*tt28*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt28
hes(2,3) = tt29
hes(2,4) = tt30
hes(2,5) = tt31
hes(2,6) = tt32
hes(2,7) = tt33
hes(2,8) = tt34
hes(2,9) = tt35
hes(3,1) = tt15
hes(3,2) = tt29
hes(3,3) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*tt14*F(3,1)*tt10)/3.0E&
&+0+(1.0E+1*tt36*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt36
hes(3,4) = tt37
hes(3,5) = tt38
hes(3,6) = tt39
hes(3,7) = tt40
hes(3,8) = tt41
hes(3,9) = tt42
hes(4,1) = tt17
hes(4,2) = tt30
hes(4,3) = tt37
hes(4,4) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*F(1,2)*tt16*tt10)/3.0E&
&+0+(1.0E+1*tt43*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt43
hes(4,5) = tt44
hes(4,6) = tt45
hes(4,7) = tt46
hes(4,8) = tt47
hes(4,9) = tt48
hes(5,1) = tt20
hes(5,2) = tt31
hes(5,3) = tt38
hes(5,4) = tt44
hes(5,5) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*F(2,2)*tt18*tt10)/3.0E&
&+0+(1.0E+1*tt49*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt49
hes(5,6) = tt50
hes(5,7) = tt51
hes(5,8) = tt52
hes(5,9) = tt53
hes(6,1) = tt22
hes(6,2) = tt32
hes(6,3) = tt39
hes(6,4) = tt45
hes(6,5) = tt50
hes(6,6) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*tt21*F(3,2)*tt10)/3.0E&
&+0+(1.0E+1*tt54*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt54
hes(6,7) = tt55
hes(6,8) = tt56
hes(6,9) = tt57
hes(7,1) = tt23
hes(7,2) = tt33
hes(7,3) = tt40
hes(7,4) = tt46
hes(7,5) = tt51
hes(7,6) = tt55
hes(7,7) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*F(1,3)*tt3*tt10)/3.0E+&
&0+(1.0E+1*tt58*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt58
hes(7,8) = tt59
hes(7,9) = tt60
hes(8,1) = tt25
hes(8,2) = tt34
hes(8,3) = tt41
hes(8,4) = tt47
hes(8,5) = tt52
hes(8,6) = tt56
hes(8,7) = tt59
hes(8,8) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*F(2,3)*tt24*tt10)/3.0E&
&+0+(1.0E+1*tt61*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt61
hes(8,9) = tt62
hes(9,1) = tt27
hes(9,2) = tt35
hes(9,3) = tt42
hes(9,4) = tt48
hes(9,5) = tt53
hes(9,6) = tt57
hes(9,7) = tt60
hes(9,8) = tt62
hes(9,9) = 5.0E-1*mu(1,1)*(tt11+((-8.0E+0)*tt26*F(3,3)*tt10)/3.0E&
&+0+(1.0E+1*tt63*tt8*tt9)/9.0E+0)+1.0E+0*lam(1,1)*tt63
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
tt1 = F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F(2,1)*F(3,3)-&
&F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-1
val(1,1) = 5.0E-1*lam(1,1)*tt1**2+5.0E-1*mu(1,1)*(F(3,3)**2+F(3,2&
&)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2+F(1,3)**2+F(1,2)**2+&
&F(1,1)**2-3)-mu(1,1)*tt1
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
tt4 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt5 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt6 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt7 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt8 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt9 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt10 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
jac(1,1) = 1.0E+0*lam(1,1)*tt1*tt3-mu(1,1)*tt1+1.0E+0*F(1,1)*mu(1&
&,1)
jac(1,2) = 1.0E+0*lam(1,1)*tt4*tt3-mu(1,1)*tt4+1.0E+0*mu(1,1)*F(2&
&,1)
jac(1,3) = 1.0E+0*lam(1,1)*tt5*tt3+1.0E+0*mu(1,1)*F(3,1)-mu(1,1)*&
&tt5
jac(1,4) = 1.0E+0*lam(1,1)*tt6*tt3-mu(1,1)*tt6+1.0E+0*mu(1,1)*F(1&
&,2)
jac(1,5) = 1.0E+0*lam(1,1)*tt7*tt3-mu(1,1)*tt7+1.0E+0*mu(1,1)*F(2&
&,2)
jac(1,6) = 1.0E+0*lam(1,1)*tt8*tt3+1.0E+0*mu(1,1)*F(3,2)-mu(1,1)*&
&tt8
jac(1,7) = 1.0E+0*lam(1,1)*tt2*tt3-mu(1,1)*tt2+1.0E+0*mu(1,1)*F(1&
&,3)
jac(1,8) = 1.0E+0*lam(1,1)*tt9*tt3-mu(1,1)*tt9+1.0E+0*mu(1,1)*F(2&
&,3)
jac(1,9) = 1.0E+0*lam(1,1)*tt10*tt3+1.0E+0*mu(1,1)*F(3,3)-mu(1,1)&
&*tt10
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
tt1 = 1.0E+0*mu(1,1)
tt2 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt3 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt4 = 1.0E+0*lam(1,1)*tt3*tt2
tt5 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt6 = 1.0E+0*lam(1,1)*tt5*tt2
tt7 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt8 = 1.0E+0*lam(1,1)*tt7*tt2
tt9 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt10 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt11 = F(1,1)*tt2-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt1&
&0-1
tt12 = 1.0E+0*lam(1,1)*F(3,3)*tt11+1.0E+0*lam(1,1)*tt9*tt2-mu(1,1&
&)*F(3,3)
tt13 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt14 = (-1.0E+0*lam(1,1)*F(2,3)*tt11)+1.0E+0*lam(1,1)*tt13*tt2+mu&
&(1,1)*F(2,3)
tt15 = 1.0E+0*lam(1,1)*tt10*tt2
tt16 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt17 = (-1.0E+0*lam(1,1)*F(3,2)*tt11)+1.0E+0*lam(1,1)*tt16*tt2+mu&
&(1,1)*F(3,2)
tt18 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt19 = 1.0E+0*lam(1,1)*F(2,2)*tt11+1.0E+0*lam(1,1)*tt18*tt2-mu(1,&
&1)*F(2,2)
tt20 = 1.0E+0*lam(1,1)*tt5*tt3
tt21 = (-1.0E+0*lam(1,1)*F(3,3)*tt11)+1.0E+0*lam(1,1)*tt3*tt7+mu(&
&1,1)*F(3,3)
tt22 = 1.0E+0*lam(1,1)*tt9*tt3
tt23 = 1.0E+0*lam(1,1)*F(1,3)*tt11+1.0E+0*lam(1,1)*tt13*tt3-mu(1,&
&1)*F(1,3)
tt24 = 1.0E+0*lam(1,1)*F(3,2)*tt11+1.0E+0*lam(1,1)*tt10*tt3-mu(1,&
&1)*F(3,2)
tt25 = 1.0E+0*lam(1,1)*tt16*tt3
tt26 = (-1.0E+0*lam(1,1)*F(1,2)*tt11)+1.0E+0*lam(1,1)*tt18*tt3+mu&
&(1,1)*F(1,2)
tt27 = 1.0E+0*lam(1,1)*F(2,3)*tt11+1.0E+0*lam(1,1)*tt5*tt7-mu(1,1&
&)*F(2,3)
tt28 = (-1.0E+0*lam(1,1)*F(1,3)*tt11)+1.0E+0*lam(1,1)*tt5*tt9+mu(&
&1,1)*F(1,3)
tt29 = 1.0E+0*lam(1,1)*tt13*tt5
tt30 = (-1.0E+0*lam(1,1)*F(2,2)*tt11)+1.0E+0*lam(1,1)*tt5*tt10+mu&
&(1,1)*F(2,2)
tt31 = 1.0E+0*lam(1,1)*F(1,2)*tt11+1.0E+0*lam(1,1)*tt5*tt16-mu(1,&
&1)*F(1,2)
tt32 = 1.0E+0*lam(1,1)*tt18*tt5
tt33 = 1.0E+0*lam(1,1)*tt9*tt7
tt34 = 1.0E+0*lam(1,1)*tt13*tt7
tt35 = 1.0E+0*lam(1,1)*tt10*tt7
tt36 = 1.0E+0*lam(1,1)*F(3,1)*tt11+1.0E+0*lam(1,1)*tt16*tt7-mu(1,&
&1)*F(3,1)
tt37 = (-1.0E+0*lam(1,1)*F(2,1)*tt11)+1.0E+0*lam(1,1)*tt18*tt7+mu&
&(1,1)*F(2,1)
tt38 = 1.0E+0*lam(1,1)*tt13*tt9
tt39 = (-1.0E+0*lam(1,1)*F(3,1)*tt11)+1.0E+0*lam(1,1)*tt10*tt9+mu&
&(1,1)*F(3,1)
tt40 = 1.0E+0*lam(1,1)*tt16*tt9
tt41 = 1.0E+0*F(1,1)*lam(1,1)*tt11+1.0E+0*lam(1,1)*tt18*tt9-F(1,1&
&)*mu(1,1)
tt42 = 1.0E+0*lam(1,1)*F(2,1)*tt11+1.0E+0*lam(1,1)*tt13*tt10-mu(1&
&,1)*F(2,1)
tt43 = (-1.0E+0*F(1,1)*lam(1,1)*tt11)+1.0E+0*lam(1,1)*tt13*tt16+F&
&(1,1)*mu(1,1)
tt44 = 1.0E+0*lam(1,1)*tt18*tt13
tt45 = 1.0E+0*lam(1,1)*tt16*tt10
tt46 = 1.0E+0*lam(1,1)*tt18*tt10
tt47 = 1.0E+0*lam(1,1)*tt18*tt16
hes(1,1) = 1.0E+0*lam(1,1)*tt2**2+tt1
hes(1,2) = tt4
hes(1,3) = tt6
hes(1,4) = tt8
hes(1,5) = tt12
hes(1,6) = tt14
hes(1,7) = tt15
hes(1,8) = tt17
hes(1,9) = tt19
hes(2,1) = tt4
hes(2,2) = 1.0E+0*lam(1,1)*tt3**2+tt1
hes(2,3) = tt20
hes(2,4) = tt21
hes(2,5) = tt22
hes(2,6) = tt23
hes(2,7) = tt24
hes(2,8) = tt25
hes(2,9) = tt26
hes(3,1) = tt6
hes(3,2) = tt20
hes(3,3) = 1.0E+0*lam(1,1)*tt5**2+tt1
hes(3,4) = tt27
hes(3,5) = tt28
hes(3,6) = tt29
hes(3,7) = tt30
hes(3,8) = tt31
hes(3,9) = tt32
hes(4,1) = tt8
hes(4,2) = tt21
hes(4,3) = tt27
hes(4,4) = 1.0E+0*lam(1,1)*tt7**2+tt1
hes(4,5) = tt33
hes(4,6) = tt34
hes(4,7) = tt35
hes(4,8) = tt36
hes(4,9) = tt37
hes(5,1) = tt12
hes(5,2) = tt22
hes(5,3) = tt28
hes(5,4) = tt33
hes(5,5) = 1.0E+0*lam(1,1)*tt9**2+tt1
hes(5,6) = tt38
hes(5,7) = tt39
hes(5,8) = tt40
hes(5,9) = tt41
hes(6,1) = tt14
hes(6,2) = tt23
hes(6,3) = tt29
hes(6,4) = tt34
hes(6,5) = tt38
hes(6,6) = 1.0E+0*lam(1,1)*tt13**2+tt1
hes(6,7) = tt42
hes(6,8) = tt43
hes(6,9) = tt44
hes(7,1) = tt15
hes(7,2) = tt24
hes(7,3) = tt30
hes(7,4) = tt35
hes(7,5) = tt39
hes(7,6) = tt42
hes(7,7) = 1.0E+0*lam(1,1)*tt10**2+tt1
hes(7,8) = tt45
hes(7,9) = tt46
hes(8,1) = tt17
hes(8,2) = tt25
hes(8,3) = tt31
hes(8,4) = tt36
hes(8,5) = tt40
hes(8,6) = tt43
hes(8,7) = tt45
hes(8,8) = 1.0E+0*lam(1,1)*tt16**2+tt1
hes(8,9) = tt47
hes(9,1) = tt19
hes(9,2) = tt26
hes(9,3) = tt32
hes(9,4) = tt37
hes(9,5) = tt41
hes(9,6) = tt44
hes(9,7) = tt46
hes(9,8) = tt47
hes(9,9) = 1.0E+0*lam(1,1)*tt18**2+tt1
END
SUBROUTINE &
&pixar18_neohookean_3d_val(&
&  val &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = F(1,3)**2
tt4 = F(2,1)**2
tt5 = F(2,2)**2
tt6 = F(2,3)**2
tt7 = F(3,1)**2
tt8 = F(3,2)**2
tt9 = F(3,3)**2
tt10 = (5.0E+0*mu(1,1))/6.0E+0+lam(1,1)
val(1,1) = (-6.666666666666666E-1*mu(1,1)*log(tt9+tt8+tt7+tt6+tt5&
&+tt4+tt3+tt2+tt1+1))+5.0E-1*tt10*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(&
&3,2))-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-&
&F(2,2)*F(3,1))-mu(1,1)/tt10-1)**2+6.666666666666666E-1*mu(1,1)*(t&
&t9+tt8+tt7+tt6+tt5+tt4+tt3+tt2+tt1-3)
END
SUBROUTINE &
&pixar18_neohookean_3d_jac(&
&  jac &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
tt1 = (5.0E+0*mu(1,1))/6.0E+0+lam(1,1)
tt2 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt3 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt4 = F(1,1)*tt2-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt3-&
&mu(1,1)/tt1-1
tt5 = 1/(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)&
&**2+F(1,3)**2+F(1,2)**2+F(1,1)**2+1)
jac(1,1) = (-1.3333333333333333E+0*F(1,1)*mu(1,1)*tt5)+1.0E+0*tt1&
&*tt2*tt4+1.3333333333333333E+0*F(1,1)*mu(1,1)
jac(1,2) = (-1.3333333333333333E+0*mu(1,1)*F(2,1)*tt5)+1.0E+0*tt1&
&*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(2,1)
jac(1,3) = (-1.3333333333333333E+0*mu(1,1)*F(3,1)*tt5)+1.0E+0*tt1&
&*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(3,1)
jac(1,4) = (-1.3333333333333333E+0*mu(1,1)*F(1,2)*tt5)+1.0E+0*tt1&
&*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(1,2)
jac(1,5) = (-1.3333333333333333E+0*mu(1,1)*F(2,2)*tt5)+1.0E+0*tt1&
&*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(2,2)
jac(1,6) = (-1.3333333333333333E+0*mu(1,1)*F(3,2)*tt5)+1.0E+0*tt1&
&*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(3,2)
jac(1,7) = (-1.3333333333333333E+0*mu(1,1)*F(1,3)*tt5)+1.0E+0*tt1&
&*tt3*tt4+1.3333333333333333E+0*mu(1,1)*F(1,3)
jac(1,8) = (-1.3333333333333333E+0*mu(1,1)*F(2,3)*tt5)+1.0E+0*tt1&
&*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(2,3)
jac(1,9) = (-1.3333333333333333E+0*mu(1,1)*F(3,3)*tt5)+1.0E+0*tt1&
&*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt4+1.3333333333333333E+0*mu(1,1)*&
&F(3,3)
END
SUBROUTINE &
&pixar18_neohookean_3d_hes(&
&  hes &
&, F &
&, lam &
&, mu &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) lam(1, 1)
REAL(KIND=8) mu(1, 1)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
tt1 = 1.3333333333333333E+0*mu(1,1)
tt2 = (5.0E+0*mu(1,1))/6.0E+0+lam(1,1)
tt3 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt4 = F(1,1)**2
tt5 = F(1,2)**2
tt6 = F(1,3)**2
tt7 = F(2,1)**2
tt8 = F(2,2)**2
tt9 = F(2,3)**2
tt10 = F(3,1)**2
tt11 = F(3,2)**2
tt12 = F(3,3)**2
tt13 = tt12+tt11+tt10+tt9+tt8+tt7+tt6+tt5+tt4+1
tt14 = 1/tt13**2
tt15 = -(1.3333333333333333E+0*mu(1,1))/tt13
tt16 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt17 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(2,1)*tt14+1.0E+0*tt&
&2*tt16*tt3
tt18 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt19 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(3,1)*tt14+1.0E+0*tt&
&2*tt18*tt3
tt20 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt21 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(1,2)*tt14+1.0E+0*tt&
&2*tt20*tt3
tt22 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt23 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt24 = F(1,1)*tt3-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2&
&3-mu(1,1)/tt2-1
tt25 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(2,2)*tt14+1.0E+0*tt&
&2*F(3,3)*tt24+1.0E+0*tt2*tt22*tt3
tt26 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt27 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(3,2)*tt14-1.0E+0*tt&
&2*F(2,3)*tt24+1.0E+0*tt2*tt26*tt3
tt28 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(1,3)*tt14+1.0E+0*tt&
&2*tt23*tt3
tt29 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt30 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(2,3)*tt14-1.0E+0*tt&
&2*F(3,2)*tt24+1.0E+0*tt2*tt29*tt3
tt31 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt32 = 2.6666666666666667E+0*F(1,1)*mu(1,1)*F(3,3)*tt14+1.0E+0*tt&
&2*F(2,2)*tt24+1.0E+0*tt2*tt31*tt3
tt33 = 2.6666666666666667E+0*mu(1,1)*F(2,1)*F(3,1)*tt14+1.0E+0*tt&
&2*tt18*tt16
tt34 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(2,1)*tt14-1.0E+0*tt&
&2*F(3,3)*tt24+1.0E+0*tt2*tt16*tt20
tt35 = 2.6666666666666667E+0*mu(1,1)*F(2,1)*F(2,2)*tt14+1.0E+0*tt&
&2*tt22*tt16
tt36 = 2.6666666666666667E+0*mu(1,1)*F(2,1)*F(3,2)*tt14+1.0E+0*tt&
&2*F(1,3)*tt24+1.0E+0*tt2*tt26*tt16
tt37 = 2.6666666666666667E+0*mu(1,1)*F(1,3)*F(2,1)*tt14+1.0E+0*tt&
&2*F(3,2)*tt24+1.0E+0*tt2*tt23*tt16
tt38 = 2.6666666666666667E+0*mu(1,1)*F(2,1)*F(2,3)*tt14+1.0E+0*tt&
&2*tt29*tt16
tt39 = 2.6666666666666667E+0*mu(1,1)*F(2,1)*F(3,3)*tt14-1.0E+0*tt&
&2*F(1,2)*tt24+1.0E+0*tt2*tt31*tt16
tt40 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(3,1)*tt14+1.0E+0*tt&
&2*F(2,3)*tt24+1.0E+0*tt2*tt18*tt20
tt41 = 2.6666666666666667E+0*mu(1,1)*F(2,2)*F(3,1)*tt14-1.0E+0*tt&
&2*F(1,3)*tt24+1.0E+0*tt2*tt18*tt22
tt42 = 2.6666666666666667E+0*mu(1,1)*F(3,1)*F(3,2)*tt14+1.0E+0*tt&
&2*tt26*tt18
tt43 = 2.6666666666666667E+0*mu(1,1)*F(1,3)*F(3,1)*tt14-1.0E+0*tt&
&2*F(2,2)*tt24+1.0E+0*tt2*tt18*tt23
tt44 = 2.6666666666666667E+0*mu(1,1)*F(2,3)*F(3,1)*tt14+1.0E+0*tt&
&2*F(1,2)*tt24+1.0E+0*tt2*tt18*tt29
tt45 = 2.6666666666666667E+0*mu(1,1)*F(3,1)*F(3,3)*tt14+1.0E+0*tt&
&2*tt31*tt18
tt46 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(2,2)*tt14+1.0E+0*tt&
&2*tt22*tt20
tt47 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(3,2)*tt14+1.0E+0*tt&
&2*tt26*tt20
tt48 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(1,3)*tt14+1.0E+0*tt&
&2*tt23*tt20
tt49 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(2,3)*tt14+1.0E+0*tt&
&2*F(3,1)*tt24+1.0E+0*tt2*tt29*tt20
tt50 = 2.6666666666666667E+0*mu(1,1)*F(1,2)*F(3,3)*tt14-1.0E+0*tt&
&2*F(2,1)*tt24+1.0E+0*tt2*tt31*tt20
tt51 = 2.6666666666666667E+0*mu(1,1)*F(2,2)*F(3,2)*tt14+1.0E+0*tt&
&2*tt26*tt22
tt52 = 2.6666666666666667E+0*mu(1,1)*F(1,3)*F(2,2)*tt14-1.0E+0*tt&
&2*F(3,1)*tt24+1.0E+0*tt2*tt23*tt22
tt53 = 2.6666666666666667E+0*mu(1,1)*F(2,2)*F(2,3)*tt14+1.0E+0*tt&
&2*tt29*tt22
tt54 = 2.6666666666666667E+0*mu(1,1)*F(2,2)*F(3,3)*tt14+1.0E+0*F(&
&1,1)*tt2*tt24+1.0E+0*tt2*tt31*tt22
tt55 = 2.6666666666666667E+0*mu(1,1)*F(1,3)*F(3,2)*tt14+1.0E+0*tt&
&2*F(2,1)*tt24+1.0E+0*tt2*tt26*tt23
tt56 = 2.6666666666666667E+0*mu(1,1)*F(2,3)*F(3,2)*tt14-1.0E+0*F(&
&1,1)*tt2*tt24+1.0E+0*tt2*tt26*tt29
tt57 = 2.6666666666666667E+0*mu(1,1)*F(3,2)*F(3,3)*tt14+1.0E+0*tt&
&2*tt31*tt26
tt58 = 2.6666666666666667E+0*mu(1,1)*F(1,3)*F(2,3)*tt14+1.0E+0*tt&
&2*tt29*tt23
tt59 = 2.6666666666666667E+0*mu(1,1)*F(1,3)*F(3,3)*tt14+1.0E+0*tt&
&2*tt31*tt23
tt60 = 2.6666666666666667E+0*mu(1,1)*F(2,3)*F(3,3)*tt14+1.0E+0*tt&
&2*tt31*tt29
hes(1,1) = tt15+2.6666666666666667E+0*tt4*mu(1,1)*tt14+1.0E+0*tt2&
&*tt3**2+tt1
hes(1,2) = tt17
hes(1,3) = tt19
hes(1,4) = tt21
hes(1,5) = tt25
hes(1,6) = tt27
hes(1,7) = tt28
hes(1,8) = tt30
hes(1,9) = tt32
hes(2,1) = tt17
hes(2,2) = tt15+2.6666666666666667E+0*mu(1,1)*tt7*tt14+1.0E+0*tt2&
&*tt16**2+tt1
hes(2,3) = tt33
hes(2,4) = tt34
hes(2,5) = tt35
hes(2,6) = tt36
hes(2,7) = tt37
hes(2,8) = tt38
hes(2,9) = tt39
hes(3,1) = tt19
hes(3,2) = tt33
hes(3,3) = tt15+2.6666666666666667E+0*mu(1,1)*tt10*tt14+1.0E+0*tt&
&2*tt18**2+tt1
hes(3,4) = tt40
hes(3,5) = tt41
hes(3,6) = tt42
hes(3,7) = tt43
hes(3,8) = tt44
hes(3,9) = tt45
hes(4,1) = tt21
hes(4,2) = tt34
hes(4,3) = tt40
hes(4,4) = tt15+2.6666666666666667E+0*mu(1,1)*tt5*tt14+1.0E+0*tt2&
&*tt20**2+tt1
hes(4,5) = tt46
hes(4,6) = tt47
hes(4,7) = tt48
hes(4,8) = tt49
hes(4,9) = tt50
hes(5,1) = tt25
hes(5,2) = tt35
hes(5,3) = tt41
hes(5,4) = tt46
hes(5,5) = tt15+2.6666666666666667E+0*mu(1,1)*tt8*tt14+1.0E+0*tt2&
&*tt22**2+tt1
hes(5,6) = tt51
hes(5,7) = tt52
hes(5,8) = tt53
hes(5,9) = tt54
hes(6,1) = tt27
hes(6,2) = tt36
hes(6,3) = tt42
hes(6,4) = tt47
hes(6,5) = tt51
hes(6,6) = tt15+2.6666666666666667E+0*mu(1,1)*tt11*tt14+1.0E+0*tt&
&2*tt26**2+tt1
hes(6,7) = tt55
hes(6,8) = tt56
hes(6,9) = tt57
hes(7,1) = tt28
hes(7,2) = tt37
hes(7,3) = tt43
hes(7,4) = tt48
hes(7,5) = tt52
hes(7,6) = tt55
hes(7,7) = tt15+2.6666666666666667E+0*mu(1,1)*tt6*tt14+1.0E+0*tt2&
&*tt23**2+tt1
hes(7,8) = tt58
hes(7,9) = tt59
hes(8,1) = tt30
hes(8,2) = tt38
hes(8,3) = tt44
hes(8,4) = tt49
hes(8,5) = tt53
hes(8,6) = tt56
hes(8,7) = tt58
hes(8,8) = tt15+2.6666666666666667E+0*mu(1,1)*tt9*tt14+1.0E+0*tt2&
&*tt29**2+tt1
hes(8,9) = tt60
hes(9,1) = tt32
hes(9,2) = tt39
hes(9,3) = tt45
hes(9,4) = tt50
hes(9,5) = tt54
hes(9,6) = tt57
hes(9,7) = tt59
hes(9,8) = tt60
hes(9,9) = tt15+2.6666666666666667E+0*mu(1,1)*tt12*tt14+1.0E+0*tt&
&2*tt31**2+tt1
END
SUBROUTINE &
&linear_elas_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(1.0E+0*F(3,3)+1.0E+0*F(2,2)+1.0E+0*F(1,1)-3)**&
&2
END
SUBROUTINE &
&linear_elas_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*(1.0E+0*F(3,3)+1.0E+0*F(2,2)+1.0E+0*F(1,1)-3)
jac(1,1) = tt1
jac(1,2) = 0
jac(1,3) = 0
jac(1,4) = 0
jac(1,5) = tt1
jac(1,6) = 0
jac(1,7) = 0
jac(1,8) = 0
jac(1,9) = tt1
END
SUBROUTINE &
&linear_elas_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
hes(1,1) = 1.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = 1.0E+0
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = 1.0E+0
hes(2,1) = 0
hes(2,2) = 0
hes(2,3) = 0
hes(2,4) = 0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 0
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 0
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = 1.0E+0
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = 1.0E+0
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = 1.0E+0
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 0
hes(6,7) = 0
hes(6,8) = 0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = 0
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 0
hes(8,7) = 0
hes(8,8) = 0
hes(8,9) = 0
hes(9,1) = 1.0E+0
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = 1.0E+0
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 1.0E+0
END
SUBROUTINE &
&linear_elas_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = (1.0E+0*F(3,3)-1)**2+5.0E-1*(F(3,2)+F(2,3))**2+5.0E-1*&
&(F(3,1)+F(1,3))**2+(1.0E+0*F(2,2)-1)**2+5.0E-1*(F(2,1)+F(1,2))**2&
&+(1.0E+0*F(1,1)-1)**2
END
SUBROUTINE &
&linear_elas_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = 1.0E+0*(F(2,1)+F(1,2))
tt2 = 1.0E+0*(F(3,1)+F(1,3))
tt3 = 1.0E+0*(F(3,2)+F(2,3))
jac(1,1) = 2.0E+0*(1.0E+0*F(1,1)-1)
jac(1,2) = tt1
jac(1,3) = tt2
jac(1,4) = tt1
jac(1,5) = 2.0E+0*(1.0E+0*F(2,2)-1)
jac(1,6) = tt3
jac(1,7) = tt2
jac(1,8) = tt3
jac(1,9) = 2.0E+0*(1.0E+0*F(3,3)-1)
END
SUBROUTINE &
&linear_elas_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
hes(1,1) = 2.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = 0
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = 0
hes(2,1) = 0
hes(2,2) = 1.0E+0
hes(2,3) = 0
hes(2,4) = 1.0E+0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 1.0E+0
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 1.0E+0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 1.0E+0
hes(4,3) = 0
hes(4,4) = 1.0E+0
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = 0
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = 2.0E+0
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = 0
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 1.0E+0
hes(6,7) = 0
hes(6,8) = 1.0E+0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 1.0E+0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = 1.0E+0
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 1.0E+0
hes(8,7) = 0
hes(8,8) = 1.0E+0
hes(8,9) = 0
hes(9,1) = 0
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = 0
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 2.0E+0
END
SUBROUTINE &
&stvk_elas_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(5.0E-1*(F(3,3)**2+F(2,3)**2+F(1,3)**2-1)+5.0E-&
&1*(F(3,2)**2+F(2,2)**2+F(1,2)**2-1)+5.0E-1*(F(3,1)**2+F(2,1)**2+F&
&(1,1)**2-1))**2
END
SUBROUTINE &
&stvk_elas_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
tt1 = 5.0E-1*(F(3,3)**2+F(2,3)**2+F(1,3)**2-1)+5.0E-1*(F(3,2)**2+&
&F(2,2)**2+F(1,2)**2-1)+5.0E-1*(F(3,1)**2+F(2,1)**2+F(1,1)**2-1)
jac(1,1) = 1.0E+0*F(1,1)*tt1
jac(1,2) = 1.0E+0*F(2,1)*tt1
jac(1,3) = 1.0E+0*F(3,1)*tt1
jac(1,4) = 1.0E+0*F(1,2)*tt1
jac(1,5) = 1.0E+0*F(2,2)*tt1
jac(1,6) = 1.0E+0*F(3,2)*tt1
jac(1,7) = 1.0E+0*F(1,3)*tt1
jac(1,8) = 1.0E+0*F(2,3)*tt1
jac(1,9) = 1.0E+0*F(3,3)*tt1
END
SUBROUTINE &
&stvk_elas_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
tt1 = F(1,1)**2
tt2 = F(2,1)**2
tt3 = F(3,1)**2
tt4 = F(1,2)**2
tt5 = F(2,2)**2
tt6 = F(3,2)**2
tt7 = F(1,3)**2
tt8 = F(2,3)**2
tt9 = F(3,3)**2
tt10 = 1.0E+0*(5.0E-1*(tt9+tt8+tt7-1)+5.0E-1*(tt6+tt5+tt4-1)+5.0E&
&-1*(tt3+tt2+tt1-1))
tt11 = 1.0E+0*F(1,1)*F(2,1)
tt12 = 1.0E+0*F(1,1)*F(3,1)
tt13 = 1.0E+0*F(1,1)*F(1,2)
tt14 = 1.0E+0*F(1,1)*F(2,2)
tt15 = 1.0E+0*F(1,1)*F(3,2)
tt16 = 1.0E+0*F(1,1)*F(1,3)
tt17 = 1.0E+0*F(1,1)*F(2,3)
tt18 = 1.0E+0*F(1,1)*F(3,3)
tt19 = 1.0E+0*F(2,1)*F(3,1)
tt20 = 1.0E+0*F(1,2)*F(2,1)
tt21 = 1.0E+0*F(2,1)*F(2,2)
tt22 = 1.0E+0*F(2,1)*F(3,2)
tt23 = 1.0E+0*F(1,3)*F(2,1)
tt24 = 1.0E+0*F(2,1)*F(2,3)
tt25 = 1.0E+0*F(2,1)*F(3,3)
tt26 = 1.0E+0*F(1,2)*F(3,1)
tt27 = 1.0E+0*F(2,2)*F(3,1)
tt28 = 1.0E+0*F(3,1)*F(3,2)
tt29 = 1.0E+0*F(1,3)*F(3,1)
tt30 = 1.0E+0*F(2,3)*F(3,1)
tt31 = 1.0E+0*F(3,1)*F(3,3)
tt32 = 1.0E+0*F(1,2)*F(2,2)
tt33 = 1.0E+0*F(1,2)*F(3,2)
tt34 = 1.0E+0*F(1,2)*F(1,3)
tt35 = 1.0E+0*F(1,2)*F(2,3)
tt36 = 1.0E+0*F(1,2)*F(3,3)
tt37 = 1.0E+0*F(2,2)*F(3,2)
tt38 = 1.0E+0*F(1,3)*F(2,2)
tt39 = 1.0E+0*F(2,2)*F(2,3)
tt40 = 1.0E+0*F(2,2)*F(3,3)
tt41 = 1.0E+0*F(1,3)*F(3,2)
tt42 = 1.0E+0*F(2,3)*F(3,2)
tt43 = 1.0E+0*F(3,2)*F(3,3)
tt44 = 1.0E+0*F(1,3)*F(2,3)
tt45 = 1.0E+0*F(1,3)*F(3,3)
tt46 = 1.0E+0*F(2,3)*F(3,3)
hes(1,1) = tt10+1.0E+0*tt1
hes(1,2) = tt11
hes(1,3) = tt12
hes(1,4) = tt13
hes(1,5) = tt14
hes(1,6) = tt15
hes(1,7) = tt16
hes(1,8) = tt17
hes(1,9) = tt18
hes(2,1) = tt11
hes(2,2) = tt10+1.0E+0*tt2
hes(2,3) = tt19
hes(2,4) = tt20
hes(2,5) = tt21
hes(2,6) = tt22
hes(2,7) = tt23
hes(2,8) = tt24
hes(2,9) = tt25
hes(3,1) = tt12
hes(3,2) = tt19
hes(3,3) = tt10+1.0E+0*tt3
hes(3,4) = tt26
hes(3,5) = tt27
hes(3,6) = tt28
hes(3,7) = tt29
hes(3,8) = tt30
hes(3,9) = tt31
hes(4,1) = tt13
hes(4,2) = tt20
hes(4,3) = tt26
hes(4,4) = tt10+1.0E+0*tt4
hes(4,5) = tt32
hes(4,6) = tt33
hes(4,7) = tt34
hes(4,8) = tt35
hes(4,9) = tt36
hes(5,1) = tt14
hes(5,2) = tt21
hes(5,3) = tt27
hes(5,4) = tt32
hes(5,5) = tt10+1.0E+0*tt5
hes(5,6) = tt37
hes(5,7) = tt38
hes(5,8) = tt39
hes(5,9) = tt40
hes(6,1) = tt15
hes(6,2) = tt22
hes(6,3) = tt28
hes(6,4) = tt33
hes(6,5) = tt37
hes(6,6) = tt10+1.0E+0*tt6
hes(6,7) = tt41
hes(6,8) = tt42
hes(6,9) = tt43
hes(7,1) = tt16
hes(7,2) = tt23
hes(7,3) = tt29
hes(7,4) = tt34
hes(7,5) = tt38
hes(7,6) = tt41
hes(7,7) = tt10+1.0E+0*tt7
hes(7,8) = tt44
hes(7,9) = tt45
hes(8,1) = tt17
hes(8,2) = tt24
hes(8,3) = tt30
hes(8,4) = tt35
hes(8,5) = tt39
hes(8,6) = tt42
hes(8,7) = tt44
hes(8,8) = tt10+1.0E+0*tt8
hes(8,9) = tt46
hes(9,1) = tt18
hes(9,2) = tt25
hes(9,3) = tt31
hes(9,4) = tt36
hes(9,5) = tt40
hes(9,6) = tt43
hes(9,7) = tt45
hes(9,8) = tt46
hes(9,9) = tt10+1.0E+0*tt9
END
SUBROUTINE &
&stvk_elas_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 2.5E-1*(F(3,3)**2+F(2,3)**2+F(1,3)**2-1)**2+5.0E-1*(F(&
&3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3))**2+5.0E-1*(F(3,1)*F(3,3)&
&+F(2,1)*F(2,3)+F(1,1)*F(1,3))**2+2.5E-1*(F(3,2)**2+F(2,2)**2+F(1,&
&2)**2-1)**2+5.0E-1*(F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2))**2&
&+2.5E-1*(F(3,1)**2+F(2,1)**2+F(1,1)**2-1)**2
END
SUBROUTINE &
&stvk_elas_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = F(3,1)**2+F(2,1)**2+F(1,1)**2-1
tt2 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt4 = F(3,2)**2+F(2,2)**2+F(1,2)**2-1
tt5 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt6 = F(3,3)**2+F(2,3)**2+F(1,3)**2-1
jac(1,1) = 1.0E+0*F(1,3)*tt3+1.0E+0*F(1,2)*tt2+1.0E+0*F(1,1)*tt1
jac(1,2) = 1.0E+0*F(2,3)*tt3+1.0E+0*F(2,2)*tt2+1.0E+0*F(2,1)*tt1
jac(1,3) = 1.0E+0*F(3,3)*tt3+1.0E+0*F(3,2)*tt2+1.0E+0*F(3,1)*tt1
jac(1,4) = 1.0E+0*F(1,3)*tt5+1.0E+0*F(1,2)*tt4+1.0E+0*F(1,1)*tt2
jac(1,5) = 1.0E+0*F(2,3)*tt5+1.0E+0*F(2,2)*tt4+1.0E+0*F(2,1)*tt2
jac(1,6) = 1.0E+0*F(3,3)*tt5+1.0E+0*F(3,2)*tt4+1.0E+0*F(3,1)*tt2
jac(1,7) = 1.0E+0*F(1,3)*tt6+1.0E+0*F(1,2)*tt5+1.0E+0*F(1,1)*tt3
jac(1,8) = 1.0E+0*F(2,3)*tt6+1.0E+0*F(2,2)*tt5+1.0E+0*F(2,1)*tt3
jac(1,9) = 1.0E+0*F(3,3)*tt6+1.0E+0*F(3,2)*tt5+1.0E+0*F(3,1)*tt3
END
SUBROUTINE &
&stvk_elas_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
REAL(KIND=8)  tt64
REAL(KIND=8)  tt65
REAL(KIND=8)  tt66
REAL(KIND=8)  tt67
REAL(KIND=8)  tt68
REAL(KIND=8)  tt69
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = 1.0E+0*tt2
tt4 = F(1,3)**2
tt5 = 1.0E+0*tt4
tt6 = F(2,1)**2
tt7 = F(3,1)**2
tt8 = 1.0E+0*(tt7+tt6+tt1-1)
tt9 = 1.0E+0*F(1,2)*F(2,2)
tt10 = 1.0E+0*F(1,3)*F(2,3)
tt11 = tt10+tt9+2.0E+0*F(1,1)*F(2,1)
tt12 = 1.0E+0*F(1,2)*F(3,2)
tt13 = 1.0E+0*F(1,3)*F(3,3)
tt14 = tt13+tt12+2.0E+0*F(1,1)*F(3,1)
tt15 = 1.0E+0*(F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt16 = tt15+1.0E+0*F(1,1)*F(1,2)
tt17 = 1.0E+0*F(1,2)*F(2,1)
tt18 = 1.0E+0*F(1,2)*F(3,1)
tt19 = 1.0E+0*(F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3))
tt20 = tt19+1.0E+0*F(1,1)*F(1,3)
tt21 = 1.0E+0*F(1,3)*F(2,1)
tt22 = 1.0E+0*F(1,3)*F(3,1)
tt23 = F(2,2)**2
tt24 = 1.0E+0*tt23
tt25 = F(2,3)**2
tt26 = 1.0E+0*tt25
tt27 = 1.0E+0*F(2,2)*F(3,2)
tt28 = 1.0E+0*F(2,3)*F(3,3)
tt29 = tt28+tt27+2.0E+0*F(2,1)*F(3,1)
tt30 = 1.0E+0*F(1,1)*F(2,2)
tt31 = tt15+1.0E+0*F(2,1)*F(2,2)
tt32 = 1.0E+0*F(2,2)*F(3,1)
tt33 = 1.0E+0*F(1,1)*F(2,3)
tt34 = tt19+1.0E+0*F(2,1)*F(2,3)
tt35 = 1.0E+0*F(2,3)*F(3,1)
tt36 = F(3,2)**2
tt37 = 1.0E+0*tt36
tt38 = F(3,3)**2
tt39 = 1.0E+0*tt38
tt40 = 1.0E+0*F(1,1)*F(3,2)
tt41 = 1.0E+0*F(2,1)*F(3,2)
tt42 = tt15+1.0E+0*F(3,1)*F(3,2)
tt43 = 1.0E+0*F(1,1)*F(3,3)
tt44 = 1.0E+0*F(2,1)*F(3,3)
tt45 = tt19+1.0E+0*F(3,1)*F(3,3)
tt46 = 1.0E+0*tt1
tt47 = 1.0E+0*(tt36+tt23+tt2-1)
tt48 = 1.0E+0*F(1,1)*F(2,1)
tt49 = tt10+2.0E+0*F(1,2)*F(2,2)+tt48
tt50 = 1.0E+0*F(1,1)*F(3,1)
tt51 = tt13+2.0E+0*F(1,2)*F(3,2)+tt50
tt52 = 1.0E+0*(F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3))
tt53 = tt52+1.0E+0*F(1,2)*F(1,3)
tt54 = 1.0E+0*F(1,3)*F(2,2)
tt55 = 1.0E+0*F(1,3)*F(3,2)
tt56 = 1.0E+0*tt6
tt57 = 1.0E+0*F(2,1)*F(3,1)
tt58 = tt28+2.0E+0*F(2,2)*F(3,2)+tt57
tt59 = 1.0E+0*F(1,2)*F(2,3)
tt60 = tt52+1.0E+0*F(2,2)*F(2,3)
tt61 = 1.0E+0*F(2,3)*F(3,2)
tt62 = 1.0E+0*tt7
tt63 = 1.0E+0*F(1,2)*F(3,3)
tt64 = 1.0E+0*F(2,2)*F(3,3)
tt65 = tt52+1.0E+0*F(3,2)*F(3,3)
tt66 = 1.0E+0*(tt38+tt25+tt4-1)
tt67 = 2.0E+0*F(1,3)*F(2,3)+tt9+tt48
tt68 = 2.0E+0*F(1,3)*F(3,3)+tt12+tt50
tt69 = 2.0E+0*F(2,3)*F(3,3)+tt27+tt57
hes(1,1) = tt8+tt5+tt3+2.0E+0*tt1
hes(1,2) = tt11
hes(1,3) = tt14
hes(1,4) = tt16
hes(1,5) = tt17
hes(1,6) = tt18
hes(1,7) = tt20
hes(1,8) = tt21
hes(1,9) = tt22
hes(2,1) = tt11
hes(2,2) = tt8+tt26+tt24+2.0E+0*tt6
hes(2,3) = tt29
hes(2,4) = tt30
hes(2,5) = tt31
hes(2,6) = tt32
hes(2,7) = tt33
hes(2,8) = tt34
hes(2,9) = tt35
hes(3,1) = tt14
hes(3,2) = tt29
hes(3,3) = tt39+tt37+tt8+2.0E+0*tt7
hes(3,4) = tt40
hes(3,5) = tt41
hes(3,6) = tt42
hes(3,7) = tt43
hes(3,8) = tt44
hes(3,9) = tt45
hes(4,1) = tt16
hes(4,2) = tt30
hes(4,3) = tt40
hes(4,4) = tt47+tt5+2.0E+0*tt2+tt46
hes(4,5) = tt49
hes(4,6) = tt51
hes(4,7) = tt53
hes(4,8) = tt54
hes(4,9) = tt55
hes(5,1) = tt17
hes(5,2) = tt31
hes(5,3) = tt41
hes(5,4) = tt49
hes(5,5) = tt47+tt26+2.0E+0*tt23+tt56
hes(5,6) = tt58
hes(5,7) = tt59
hes(5,8) = tt60
hes(5,9) = tt61
hes(6,1) = tt18
hes(6,2) = tt32
hes(6,3) = tt42
hes(6,4) = tt51
hes(6,5) = tt58
hes(6,6) = tt39+tt47+2.0E+0*tt36+tt62
hes(6,7) = tt63
hes(6,8) = tt64
hes(6,9) = tt65
hes(7,1) = tt20
hes(7,2) = tt33
hes(7,3) = tt43
hes(7,4) = tt53
hes(7,5) = tt59
hes(7,6) = tt63
hes(7,7) = tt66+2.0E+0*tt4+tt3+tt46
hes(7,8) = tt67
hes(7,9) = tt68
hes(8,1) = tt21
hes(8,2) = tt34
hes(8,3) = tt44
hes(8,4) = tt54
hes(8,5) = tt60
hes(8,6) = tt64
hes(8,7) = tt67
hes(8,8) = tt66+2.0E+0*tt25+tt24+tt56
hes(8,9) = tt69
hes(9,1) = tt22
hes(9,2) = tt35
hes(9,3) = tt45
hes(9,4) = tt55
hes(9,5) = tt61
hes(9,6) = tt65
hes(9,7) = tt68
hes(9,8) = tt69
hes(9,9) = tt66+2.0E+0*tt38+tt37+tt62
END
SUBROUTINE &
&coro_elas_lam_3d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
val(1,1) = 5.0E-1*(5.0E-1*(2*F(3,3)*R(3,3)+2*F(2,3)*R(2,3)+2*F(1,&
&3)*R(1,3))+5.0E-1*(2*F(3,2)*R(3,2)+2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2&
&))+5.0E-1*(2*F(3,1)*R(3,1)+2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-3)**2
END
SUBROUTINE &
&coro_elas_lam_3d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
tt1 = 5.0E-1*(2*F(3,3)*R(3,3)+2*F(2,3)*R(2,3)+2*F(1,3)*R(1,3))+5.&
&0E-1*(2*F(3,2)*R(3,2)+2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))+5.0E-1*(2*&
&F(3,1)*R(3,1)+2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-3
jac(1,1) = 1.0E+0*R(1,1)*tt1
jac(1,2) = 1.0E+0*R(2,1)*tt1
jac(1,3) = 1.0E+0*R(3,1)*tt1
jac(1,4) = 1.0E+0*R(1,2)*tt1
jac(1,5) = 1.0E+0*R(2,2)*tt1
jac(1,6) = 1.0E+0*R(3,2)*tt1
jac(1,7) = 1.0E+0*R(1,3)*tt1
jac(1,8) = 1.0E+0*R(2,3)*tt1
jac(1,9) = 1.0E+0*R(3,3)*tt1
END
SUBROUTINE &
&coro_elas_lam_3d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
tt1 = 1.0E+0*R(1,1)*R(2,1)
tt2 = 1.0E+0*R(1,1)*R(3,1)
tt3 = 1.0E+0*R(1,1)*R(1,2)
tt4 = 1.0E+0*R(1,1)*R(2,2)
tt5 = 1.0E+0*R(1,1)*R(3,2)
tt6 = 1.0E+0*R(1,1)*R(1,3)
tt7 = 1.0E+0*R(1,1)*R(2,3)
tt8 = 1.0E+0*R(1,1)*R(3,3)
tt9 = 1.0E+0*R(2,1)*R(3,1)
tt10 = 1.0E+0*R(1,2)*R(2,1)
tt11 = 1.0E+0*R(2,1)*R(2,2)
tt12 = 1.0E+0*R(2,1)*R(3,2)
tt13 = 1.0E+0*R(1,3)*R(2,1)
tt14 = 1.0E+0*R(2,1)*R(2,3)
tt15 = 1.0E+0*R(2,1)*R(3,3)
tt16 = 1.0E+0*R(1,2)*R(3,1)
tt17 = 1.0E+0*R(2,2)*R(3,1)
tt18 = 1.0E+0*R(3,1)*R(3,2)
tt19 = 1.0E+0*R(1,3)*R(3,1)
tt20 = 1.0E+0*R(2,3)*R(3,1)
tt21 = 1.0E+0*R(3,1)*R(3,3)
tt22 = 1.0E+0*R(1,2)*R(2,2)
tt23 = 1.0E+0*R(1,2)*R(3,2)
tt24 = 1.0E+0*R(1,2)*R(1,3)
tt25 = 1.0E+0*R(1,2)*R(2,3)
tt26 = 1.0E+0*R(1,2)*R(3,3)
tt27 = 1.0E+0*R(2,2)*R(3,2)
tt28 = 1.0E+0*R(1,3)*R(2,2)
tt29 = 1.0E+0*R(2,2)*R(2,3)
tt30 = 1.0E+0*R(2,2)*R(3,3)
tt31 = 1.0E+0*R(1,3)*R(3,2)
tt32 = 1.0E+0*R(2,3)*R(3,2)
tt33 = 1.0E+0*R(3,2)*R(3,3)
tt34 = 1.0E+0*R(1,3)*R(2,3)
tt35 = 1.0E+0*R(1,3)*R(3,3)
tt36 = 1.0E+0*R(2,3)*R(3,3)
hes(1,1) = 1.0E+0*R(1,1)**2
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt3
hes(1,5) = tt4
hes(1,6) = tt5
hes(1,7) = tt6
hes(1,8) = tt7
hes(1,9) = tt8
hes(2,1) = tt1
hes(2,2) = 1.0E+0*R(2,1)**2
hes(2,3) = tt9
hes(2,4) = tt10
hes(2,5) = tt11
hes(2,6) = tt12
hes(2,7) = tt13
hes(2,8) = tt14
hes(2,9) = tt15
hes(3,1) = tt2
hes(3,2) = tt9
hes(3,3) = 1.0E+0*R(3,1)**2
hes(3,4) = tt16
hes(3,5) = tt17
hes(3,6) = tt18
hes(3,7) = tt19
hes(3,8) = tt20
hes(3,9) = tt21
hes(4,1) = tt3
hes(4,2) = tt10
hes(4,3) = tt16
hes(4,4) = 1.0E+0*R(1,2)**2
hes(4,5) = tt22
hes(4,6) = tt23
hes(4,7) = tt24
hes(4,8) = tt25
hes(4,9) = tt26
hes(5,1) = tt4
hes(5,2) = tt11
hes(5,3) = tt17
hes(5,4) = tt22
hes(5,5) = 1.0E+0*R(2,2)**2
hes(5,6) = tt27
hes(5,7) = tt28
hes(5,8) = tt29
hes(5,9) = tt30
hes(6,1) = tt5
hes(6,2) = tt12
hes(6,3) = tt18
hes(6,4) = tt23
hes(6,5) = tt27
hes(6,6) = 1.0E+0*R(3,2)**2
hes(6,7) = tt31
hes(6,8) = tt32
hes(6,9) = tt33
hes(7,1) = tt6
hes(7,2) = tt13
hes(7,3) = tt19
hes(7,4) = tt24
hes(7,5) = tt28
hes(7,6) = tt31
hes(7,7) = 1.0E+0*R(1,3)**2
hes(7,8) = tt34
hes(7,9) = tt35
hes(8,1) = tt7
hes(8,2) = tt14
hes(8,3) = tt20
hes(8,4) = tt25
hes(8,5) = tt29
hes(8,6) = tt32
hes(8,7) = tt34
hes(8,8) = 1.0E+0*R(2,3)**2
hes(8,9) = tt36
hes(9,1) = tt8
hes(9,2) = tt15
hes(9,3) = tt21
hes(9,4) = tt26
hes(9,5) = tt30
hes(9,6) = tt33
hes(9,7) = tt35
hes(9,8) = tt36
hes(9,9) = 1.0E+0*R(3,3)**2
END
SUBROUTINE &
&coro_elas_mu_3d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
val(1,1) = (1.0E+0*F(3,3)*R(3,3)+1.0E+0*F(2,3)*R(2,3)+1.0E+0*F(1,&
&3)*R(1,3)-1)**2+5.0E-1*(F(3,2)*R(3,3)+R(3,2)*F(3,3)+F(2,2)*R(2,3)&
&+R(2,2)*F(2,3)+F(1,2)*R(1,3)+R(1,2)*F(1,3))**2+5.0E-1*(F(3,1)*R(3&
&,3)+R(3,1)*F(3,3)+F(2,1)*R(2,3)+R(2,1)*F(2,3)+F(1,1)*R(1,3)+R(1,1&
&)*F(1,3))**2+(1.0E+0*F(3,2)*R(3,2)+1.0E+0*F(2,2)*R(2,2)+1.0E+0*F(&
&1,2)*R(1,2)-1)**2+5.0E-1*(F(3,1)*R(3,2)+R(3,1)*F(3,2)+F(2,1)*R(2,&
&2)+R(2,1)*F(2,2)+F(1,1)*R(1,2)+R(1,1)*F(1,2))**2+(1.0E+0*F(3,1)*R&
&(3,1)+1.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1,1)-1)**2
END
SUBROUTINE &
&coro_elas_mu_3d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = 1.0E+0*F(3,1)*R(3,1)+1.0E+0*F(2,1)*R(2,1)+1.0E+0*F(1,1)*R(1&
&,1)-1
tt2 = F(3,1)*R(3,2)+R(3,1)*F(3,2)+F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1&
&,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = F(3,1)*R(3,3)+R(3,1)*F(3,3)+F(2,1)*R(2,3)+R(2,1)*F(2,3)+F(1&
&,1)*R(1,3)+R(1,1)*F(1,3)
tt4 = 1.0E+0*F(3,2)*R(3,2)+1.0E+0*F(2,2)*R(2,2)+1.0E+0*F(1,2)*R(1&
&,2)-1
tt5 = F(3,2)*R(3,3)+R(3,2)*F(3,3)+F(2,2)*R(2,3)+R(2,2)*F(2,3)+F(1&
&,2)*R(1,3)+R(1,2)*F(1,3)
tt6 = 1.0E+0*F(3,3)*R(3,3)+1.0E+0*F(2,3)*R(2,3)+1.0E+0*F(1,3)*R(1&
&,3)-1
jac(1,1) = 1.0E+0*R(1,3)*tt3+1.0E+0*R(1,2)*tt2+2.0E+0*R(1,1)*tt1
jac(1,2) = 1.0E+0*R(2,3)*tt3+1.0E+0*R(2,2)*tt2+2.0E+0*R(2,1)*tt1
jac(1,3) = 1.0E+0*R(3,3)*tt3+1.0E+0*R(3,2)*tt2+2.0E+0*R(3,1)*tt1
jac(1,4) = 1.0E+0*R(1,3)*tt5+2.0E+0*R(1,2)*tt4+1.0E+0*R(1,1)*tt2
jac(1,5) = 1.0E+0*R(2,3)*tt5+2.0E+0*R(2,2)*tt4+1.0E+0*R(2,1)*tt2
jac(1,6) = 1.0E+0*R(3,3)*tt5+2.0E+0*R(3,2)*tt4+1.0E+0*R(3,1)*tt2
jac(1,7) = 2.0E+0*R(1,3)*tt6+1.0E+0*R(1,2)*tt5+1.0E+0*R(1,1)*tt3
jac(1,8) = 2.0E+0*R(2,3)*tt6+1.0E+0*R(2,2)*tt5+1.0E+0*R(2,1)*tt3
jac(1,9) = 2.0E+0*R(3,3)*tt6+1.0E+0*R(3,2)*tt5+1.0E+0*R(3,1)*tt3
END
SUBROUTINE &
&coro_elas_mu_3d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
tt1 = R(1,1)**2
tt2 = R(1,2)**2
tt3 = 1.0E+0*tt2
tt4 = R(1,3)**2
tt5 = 1.0E+0*tt4
tt6 = 1.0E+0*R(1,2)*R(2,2)
tt7 = 1.0E+0*R(1,3)*R(2,3)
tt8 = tt7+tt6+2.0E+0*R(1,1)*R(2,1)
tt9 = 1.0E+0*R(1,2)*R(3,2)
tt10 = 1.0E+0*R(1,3)*R(3,3)
tt11 = tt10+tt9+2.0E+0*R(1,1)*R(3,1)
tt12 = 1.0E+0*R(1,1)*R(1,2)
tt13 = 1.0E+0*R(1,2)*R(2,1)
tt14 = 1.0E+0*R(1,2)*R(3,1)
tt15 = 1.0E+0*R(1,1)*R(1,3)
tt16 = 1.0E+0*R(1,3)*R(2,1)
tt17 = 1.0E+0*R(1,3)*R(3,1)
tt18 = R(2,1)**2
tt19 = R(2,2)**2
tt20 = 1.0E+0*tt19
tt21 = R(2,3)**2
tt22 = 1.0E+0*tt21
tt23 = 1.0E+0*R(2,2)*R(3,2)
tt24 = 1.0E+0*R(2,3)*R(3,3)
tt25 = tt24+tt23+2.0E+0*R(2,1)*R(3,1)
tt26 = 1.0E+0*R(1,1)*R(2,2)
tt27 = 1.0E+0*R(2,1)*R(2,2)
tt28 = 1.0E+0*R(2,2)*R(3,1)
tt29 = 1.0E+0*R(1,1)*R(2,3)
tt30 = 1.0E+0*R(2,1)*R(2,3)
tt31 = 1.0E+0*R(2,3)*R(3,1)
tt32 = R(3,1)**2
tt33 = R(3,2)**2
tt34 = 1.0E+0*tt33
tt35 = R(3,3)**2
tt36 = 1.0E+0*tt35
tt37 = 1.0E+0*R(1,1)*R(3,2)
tt38 = 1.0E+0*R(2,1)*R(3,2)
tt39 = 1.0E+0*R(3,1)*R(3,2)
tt40 = 1.0E+0*R(1,1)*R(3,3)
tt41 = 1.0E+0*R(2,1)*R(3,3)
tt42 = 1.0E+0*R(3,1)*R(3,3)
tt43 = 1.0E+0*tt1
tt44 = 1.0E+0*R(1,1)*R(2,1)
tt45 = tt7+2.0E+0*R(1,2)*R(2,2)+tt44
tt46 = 1.0E+0*R(1,1)*R(3,1)
tt47 = tt10+2.0E+0*R(1,2)*R(3,2)+tt46
tt48 = 1.0E+0*R(1,2)*R(1,3)
tt49 = 1.0E+0*R(1,3)*R(2,2)
tt50 = 1.0E+0*R(1,3)*R(3,2)
tt51 = 1.0E+0*tt18
tt52 = 1.0E+0*R(2,1)*R(3,1)
tt53 = tt24+2.0E+0*R(2,2)*R(3,2)+tt52
tt54 = 1.0E+0*R(1,2)*R(2,3)
tt55 = 1.0E+0*R(2,2)*R(2,3)
tt56 = 1.0E+0*R(2,3)*R(3,2)
tt57 = 1.0E+0*tt32
tt58 = 1.0E+0*R(1,2)*R(3,3)
tt59 = 1.0E+0*R(2,2)*R(3,3)
tt60 = 1.0E+0*R(3,2)*R(3,3)
tt61 = 2.0E+0*R(1,3)*R(2,3)+tt6+tt44
tt62 = 2.0E+0*R(1,3)*R(3,3)+tt9+tt46
tt63 = 2.0E+0*R(2,3)*R(3,3)+tt23+tt52
hes(1,1) = tt5+tt3+2.0E+0*tt1
hes(1,2) = tt8
hes(1,3) = tt11
hes(1,4) = tt12
hes(1,5) = tt13
hes(1,6) = tt14
hes(1,7) = tt15
hes(1,8) = tt16
hes(1,9) = tt17
hes(2,1) = tt8
hes(2,2) = tt22+tt20+2.0E+0*tt18
hes(2,3) = tt25
hes(2,4) = tt26
hes(2,5) = tt27
hes(2,6) = tt28
hes(2,7) = tt29
hes(2,8) = tt30
hes(2,9) = tt31
hes(3,1) = tt11
hes(3,2) = tt25
hes(3,3) = tt36+tt34+2.0E+0*tt32
hes(3,4) = tt37
hes(3,5) = tt38
hes(3,6) = tt39
hes(3,7) = tt40
hes(3,8) = tt41
hes(3,9) = tt42
hes(4,1) = tt12
hes(4,2) = tt26
hes(4,3) = tt37
hes(4,4) = tt5+2.0E+0*tt2+tt43
hes(4,5) = tt45
hes(4,6) = tt47
hes(4,7) = tt48
hes(4,8) = tt49
hes(4,9) = tt50
hes(5,1) = tt13
hes(5,2) = tt27
hes(5,3) = tt38
hes(5,4) = tt45
hes(5,5) = tt22+2.0E+0*tt19+tt51
hes(5,6) = tt53
hes(5,7) = tt54
hes(5,8) = tt55
hes(5,9) = tt56
hes(6,1) = tt14
hes(6,2) = tt28
hes(6,3) = tt39
hes(6,4) = tt47
hes(6,5) = tt53
hes(6,6) = tt36+2.0E+0*tt33+tt57
hes(6,7) = tt58
hes(6,8) = tt59
hes(6,9) = tt60
hes(7,1) = tt15
hes(7,2) = tt29
hes(7,3) = tt40
hes(7,4) = tt48
hes(7,5) = tt54
hes(7,6) = tt58
hes(7,7) = 2.0E+0*tt4+tt3+tt43
hes(7,8) = tt61
hes(7,9) = tt62
hes(8,1) = tt16
hes(8,2) = tt30
hes(8,3) = tt41
hes(8,4) = tt49
hes(8,5) = tt55
hes(8,6) = tt59
hes(8,7) = tt61
hes(8,8) = 2.0E+0*tt21+tt20+tt51
hes(8,9) = tt63
hes(9,1) = tt17
hes(9,2) = tt31
hes(9,3) = tt42
hes(9,4) = tt50
hes(9,5) = tt56
hes(9,6) = tt60
hes(9,7) = tt62
hes(9,8) = tt63
hes(9,9) = 2.0E+0*tt35+tt34+tt57
END
SUBROUTINE &
&mcadams_coro_elas_lam_3d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
val(1,1) = 5.0E-1*((-R(3,3))+F(3,3)-R(2,2)+F(2,2)-R(1,1)+F(1,1))*&
&*2
END
SUBROUTINE &
&mcadams_coro_elas_lam_3d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
tt1 = 1.0E+0*((-R(3,3))+F(3,3)-R(2,2)+F(2,2)-R(1,1)+F(1,1))
jac(1,1) = tt1
jac(1,2) = 0
jac(1,3) = 0
jac(1,4) = 0
jac(1,5) = tt1
jac(1,6) = 0
jac(1,7) = 0
jac(1,8) = 0
jac(1,9) = tt1
END
SUBROUTINE &
&mcadams_coro_elas_lam_3d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
hes(1,1) = 1.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = 1.0E+0
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = 1.0E+0
hes(2,1) = 0
hes(2,2) = 0
hes(2,3) = 0
hes(2,4) = 0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 0
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 0
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = 1.0E+0
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = 1.0E+0
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = 1.0E+0
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 0
hes(6,7) = 0
hes(6,8) = 0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = 0
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 0
hes(8,7) = 0
hes(8,8) = 0
hes(8,9) = 0
hes(9,1) = 1.0E+0
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = 1.0E+0
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 1.0E+0
END
SUBROUTINE &
&mcadams_coro_elas_mu_3d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
val(1,1) = (R(3,3)-F(3,3))**2+(R(3,2)-F(3,2))**2+(R(3,1)-F(3,1))*&
&*2+(R(2,3)-F(2,3))**2+(R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))**2+(R(1,&
&3)-F(1,3))**2+(R(1,2)-F(1,2))**2+(R(1,1)-F(1,1))**2
END
SUBROUTINE &
&mcadams_coro_elas_mu_3d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
jac(1,1) = -2*(R(1,1)-F(1,1))
jac(1,2) = -2*(R(2,1)-F(2,1))
jac(1,3) = -2*(R(3,1)-F(3,1))
jac(1,4) = -2*(R(1,2)-F(1,2))
jac(1,5) = -2*(R(2,2)-F(2,2))
jac(1,6) = -2*(R(3,2)-F(3,2))
jac(1,7) = -2*(R(1,3)-F(1,3))
jac(1,8) = -2*(R(2,3)-F(2,3))
jac(1,9) = -2*(R(3,3)-F(3,3))
END
SUBROUTINE &
&mcadams_coro_elas_mu_3d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
hes(1,1) = 2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = 0
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = 0
hes(2,1) = 0
hes(2,2) = 2
hes(2,3) = 0
hes(2,4) = 0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 2
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = 0
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = 2
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = 0
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 2
hes(6,7) = 0
hes(6,8) = 0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = 2
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 0
hes(8,7) = 0
hes(8,8) = 2
hes(8,9) = 0
hes(9,1) = 0
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = 0
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_lam_3d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
val(1,1) = 5.0E-1*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F&
&(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-&
&1)**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_lam_3d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
jac(1,1) = 1.0E+0*tt1*tt3
jac(1,2) = 1.0E+0*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*tt2*tt3
jac(1,8) = 1.0E+0*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_lam_3d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt3 = 1.0E+0*tt2*tt1
tt4 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt5 = 1.0E+0*tt4*tt1
tt6 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt7 = 1.0E+0*tt6*tt1
tt8 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt9 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt10 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt9&
&-1
tt11 = 1.0E+0*F(3,3)*tt10+1.0E+0*tt8*tt1
tt12 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt13 = 1.0E+0*tt12*tt1-1.0E+0*F(2,3)*tt10
tt14 = 1.0E+0*tt9*tt1
tt15 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt16 = 1.0E+0*tt15*tt1-1.0E+0*F(3,2)*tt10
tt17 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt18 = 1.0E+0*F(2,2)*tt10+1.0E+0*tt17*tt1
tt19 = 1.0E+0*tt4*tt2
tt20 = 1.0E+0*tt2*tt6-1.0E+0*F(3,3)*tt10
tt21 = 1.0E+0*tt8*tt2
tt22 = 1.0E+0*F(1,3)*tt10+1.0E+0*tt12*tt2
tt23 = 1.0E+0*F(3,2)*tt10+1.0E+0*tt9*tt2
tt24 = 1.0E+0*tt15*tt2
tt25 = 1.0E+0*tt17*tt2-1.0E+0*F(1,2)*tt10
tt26 = 1.0E+0*F(2,3)*tt10+1.0E+0*tt4*tt6
tt27 = 1.0E+0*tt4*tt8-1.0E+0*F(1,3)*tt10
tt28 = 1.0E+0*tt12*tt4
tt29 = 1.0E+0*tt4*tt9-1.0E+0*F(2,2)*tt10
tt30 = 1.0E+0*F(1,2)*tt10+1.0E+0*tt4*tt15
tt31 = 1.0E+0*tt17*tt4
tt32 = 1.0E+0*tt8*tt6
tt33 = 1.0E+0*tt12*tt6
tt34 = 1.0E+0*tt9*tt6
tt35 = 1.0E+0*F(3,1)*tt10+1.0E+0*tt15*tt6
tt36 = 1.0E+0*tt17*tt6-1.0E+0*F(2,1)*tt10
tt37 = 1.0E+0*tt12*tt8
tt38 = 1.0E+0*tt9*tt8-1.0E+0*F(3,1)*tt10
tt39 = 1.0E+0*tt15*tt8
tt40 = 1.0E+0*F(1,1)*tt10+1.0E+0*tt17*tt8
tt41 = 1.0E+0*F(2,1)*tt10+1.0E+0*tt12*tt9
tt42 = 1.0E+0*tt12*tt15-1.0E+0*F(1,1)*tt10
tt43 = 1.0E+0*tt17*tt12
tt44 = 1.0E+0*tt15*tt9
tt45 = 1.0E+0*tt17*tt9
tt46 = 1.0E+0*tt17*tt15
hes(1,1) = 1.0E+0*tt1**2
hes(1,2) = tt3
hes(1,3) = tt5
hes(1,4) = tt7
hes(1,5) = tt11
hes(1,6) = tt13
hes(1,7) = tt14
hes(1,8) = tt16
hes(1,9) = tt18
hes(2,1) = tt3
hes(2,2) = 1.0E+0*tt2**2
hes(2,3) = tt19
hes(2,4) = tt20
hes(2,5) = tt21
hes(2,6) = tt22
hes(2,7) = tt23
hes(2,8) = tt24
hes(2,9) = tt25
hes(3,1) = tt5
hes(3,2) = tt19
hes(3,3) = 1.0E+0*tt4**2
hes(3,4) = tt26
hes(3,5) = tt27
hes(3,6) = tt28
hes(3,7) = tt29
hes(3,8) = tt30
hes(3,9) = tt31
hes(4,1) = tt7
hes(4,2) = tt20
hes(4,3) = tt26
hes(4,4) = 1.0E+0*tt6**2
hes(4,5) = tt32
hes(4,6) = tt33
hes(4,7) = tt34
hes(4,8) = tt35
hes(4,9) = tt36
hes(5,1) = tt11
hes(5,2) = tt21
hes(5,3) = tt27
hes(5,4) = tt32
hes(5,5) = 1.0E+0*tt8**2
hes(5,6) = tt37
hes(5,7) = tt38
hes(5,8) = tt39
hes(5,9) = tt40
hes(6,1) = tt13
hes(6,2) = tt22
hes(6,3) = tt28
hes(6,4) = tt33
hes(6,5) = tt37
hes(6,6) = 1.0E+0*tt12**2
hes(6,7) = tt41
hes(6,8) = tt42
hes(6,9) = tt43
hes(7,1) = tt14
hes(7,2) = tt23
hes(7,3) = tt29
hes(7,4) = tt34
hes(7,5) = tt38
hes(7,6) = tt41
hes(7,7) = 1.0E+0*tt9**2
hes(7,8) = tt44
hes(7,9) = tt45
hes(8,1) = tt16
hes(8,2) = tt24
hes(8,3) = tt30
hes(8,4) = tt35
hes(8,5) = tt39
hes(8,6) = tt42
hes(8,7) = tt44
hes(8,8) = 1.0E+0*tt15**2
hes(8,9) = tt46
hes(9,1) = tt18
hes(9,2) = tt25
hes(9,3) = tt31
hes(9,4) = tt36
hes(9,5) = tt40
hes(9,6) = tt43
hes(9,7) = tt45
hes(9,8) = tt46
hes(9,9) = 1.0E+0*tt17**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_mu_3d_val(&
&  val &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
val(1,1) = (R(3,3)-F(3,3))**2+(R(3,2)-F(3,2))**2+(R(3,1)-F(3,1))*&
&*2+(R(2,3)-F(2,3))**2+(R(2,2)-F(2,2))**2+(R(2,1)-F(2,1))**2+(R(1,&
&3)-F(1,3))**2+(R(1,2)-F(1,2))**2+(R(1,1)-F(1,1))**2
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_mu_3d_jac(&
&  jac &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
jac(1,1) = -2*(R(1,1)-F(1,1))
jac(1,2) = -2*(R(2,1)-F(2,1))
jac(1,3) = -2*(R(3,1)-F(3,1))
jac(1,4) = -2*(R(1,2)-F(1,2))
jac(1,5) = -2*(R(2,2)-F(2,2))
jac(1,6) = -2*(R(3,2)-F(3,2))
jac(1,7) = -2*(R(1,3)-F(1,3))
jac(1,8) = -2*(R(2,3)-F(2,3))
jac(1,9) = -2*(R(3,3)-F(3,3))
END
SUBROUTINE &
&stomakhin_fixedcoro_elas_mu_3d_hes(&
&  hes &
&, F &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) R(3, 3)
hes(1,1) = 2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = 0
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = 0
hes(2,1) = 0
hes(2,2) = 2
hes(2,3) = 0
hes(2,4) = 0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 2
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = 0
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = 2
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = 0
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 2
hes(6,7) = 0
hes(6,8) = 0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = 2
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 0
hes(8,7) = 0
hes(8,8) = 2
hes(8,9) = 0
hes(9,1) = 0
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = 0
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 2
END
SUBROUTINE &
&bonet08_neohookean_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*log(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)&
&*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1&
&)))**2
END
SUBROUTINE &
&bonet08_neohookean_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2
tt4 = 1/tt3
tt5 = log(tt3)
jac(1,1) = 1.0E+0*tt1*tt4*tt5
jac(1,2) = 1.0E+0*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt4*tt5
jac(1,3) = 1.0E+0*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt4*tt5
jac(1,4) = 1.0E+0*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt4*tt5
jac(1,5) = 1.0E+0*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt4*tt5
jac(1,6) = 1.0E+0*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt4*tt5
jac(1,7) = 1.0E+0*tt2*tt4*tt5
jac(1,8) = 1.0E+0*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt4*tt5
jac(1,9) = 1.0E+0*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt4*tt5
END
SUBROUTINE &
&bonet08_neohookean_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = tt1**2
tt3 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt4 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt3
tt5 = 1/tt4**2
tt6 = log(tt4)
tt7 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt8 = 1.0E+0*tt7*tt1*tt5-1.0E+0*tt7*tt1*tt5*tt6
tt9 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt10 = 1.0E+0*tt9*tt1*tt5-1.0E+0*tt9*tt1*tt5*tt6
tt11 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt12 = 1.0E+0*tt11*tt1*tt5-1.0E+0*tt11*tt1*tt5*tt6
tt13 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt14 = 1/tt4
tt15 = 1.0E+0*F(3,3)*tt14*tt6-1.0E+0*tt13*tt1*tt5*tt6+1.0E+0*tt13&
&*tt1*tt5
tt16 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt17 = (-1.0E+0*F(2,3)*tt14*tt6)-1.0E+0*tt16*tt1*tt5*tt6+1.0E+0*t&
&t16*tt1*tt5
tt18 = 1.0E+0*tt3*tt1*tt5-1.0E+0*tt3*tt1*tt5*tt6
tt19 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt20 = (-1.0E+0*F(3,2)*tt14*tt6)-1.0E+0*tt19*tt1*tt5*tt6+1.0E+0*t&
&t19*tt1*tt5
tt21 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt22 = 1.0E+0*F(2,2)*tt14*tt6-1.0E+0*tt21*tt1*tt5*tt6+1.0E+0*tt21&
&*tt1*tt5
tt23 = tt7**2
tt24 = 1.0E+0*tt9*tt7*tt5-1.0E+0*tt9*tt7*tt5*tt6
tt25 = (-1.0E+0*F(3,3)*tt14*tt6)-1.0E+0*tt7*tt11*tt5*tt6+1.0E+0*t&
&t7*tt11*tt5
tt26 = 1.0E+0*tt13*tt7*tt5-1.0E+0*tt13*tt7*tt5*tt6
tt27 = 1.0E+0*F(1,3)*tt14*tt6-1.0E+0*tt16*tt7*tt5*tt6+1.0E+0*tt16&
&*tt7*tt5
tt28 = 1.0E+0*F(3,2)*tt14*tt6-1.0E+0*tt3*tt7*tt5*tt6+1.0E+0*tt3*t&
&t7*tt5
tt29 = 1.0E+0*tt19*tt7*tt5-1.0E+0*tt19*tt7*tt5*tt6
tt30 = (-1.0E+0*F(1,2)*tt14*tt6)-1.0E+0*tt21*tt7*tt5*tt6+1.0E+0*t&
&t21*tt7*tt5
tt31 = tt9**2
tt32 = 1.0E+0*F(2,3)*tt14*tt6-1.0E+0*tt9*tt11*tt5*tt6+1.0E+0*tt9*&
&tt11*tt5
tt33 = (-1.0E+0*F(1,3)*tt14*tt6)-1.0E+0*tt9*tt13*tt5*tt6+1.0E+0*t&
&t9*tt13*tt5
tt34 = 1.0E+0*tt16*tt9*tt5-1.0E+0*tt16*tt9*tt5*tt6
tt35 = (-1.0E+0*F(2,2)*tt14*tt6)-1.0E+0*tt9*tt3*tt5*tt6+1.0E+0*tt&
&9*tt3*tt5
tt36 = 1.0E+0*F(1,2)*tt14*tt6-1.0E+0*tt9*tt19*tt5*tt6+1.0E+0*tt9*&
&tt19*tt5
tt37 = 1.0E+0*tt21*tt9*tt5-1.0E+0*tt21*tt9*tt5*tt6
tt38 = tt11**2
tt39 = 1.0E+0*tt13*tt11*tt5-1.0E+0*tt13*tt11*tt5*tt6
tt40 = 1.0E+0*tt16*tt11*tt5-1.0E+0*tt16*tt11*tt5*tt6
tt41 = 1.0E+0*tt3*tt11*tt5-1.0E+0*tt3*tt11*tt5*tt6
tt42 = 1.0E+0*F(3,1)*tt14*tt6-1.0E+0*tt19*tt11*tt5*tt6+1.0E+0*tt1&
&9*tt11*tt5
tt43 = (-1.0E+0*F(2,1)*tt14*tt6)-1.0E+0*tt21*tt11*tt5*tt6+1.0E+0*&
&tt21*tt11*tt5
tt44 = tt13**2
tt45 = 1.0E+0*tt16*tt13*tt5-1.0E+0*tt16*tt13*tt5*tt6
tt46 = (-1.0E+0*F(3,1)*tt14*tt6)-1.0E+0*tt3*tt13*tt5*tt6+1.0E+0*t&
&t3*tt13*tt5
tt47 = 1.0E+0*tt19*tt13*tt5-1.0E+0*tt19*tt13*tt5*tt6
tt48 = 1.0E+0*F(1,1)*tt14*tt6-1.0E+0*tt21*tt13*tt5*tt6+1.0E+0*tt2&
&1*tt13*tt5
tt49 = tt16**2
tt50 = 1.0E+0*F(2,1)*tt14*tt6-1.0E+0*tt16*tt3*tt5*tt6+1.0E+0*tt16&
&*tt3*tt5
tt51 = (-1.0E+0*F(1,1)*tt14*tt6)-1.0E+0*tt16*tt19*tt5*tt6+1.0E+0*&
&tt16*tt19*tt5
tt52 = 1.0E+0*tt21*tt16*tt5-1.0E+0*tt21*tt16*tt5*tt6
tt53 = tt3**2
tt54 = 1.0E+0*tt19*tt3*tt5-1.0E+0*tt19*tt3*tt5*tt6
tt55 = 1.0E+0*tt21*tt3*tt5-1.0E+0*tt21*tt3*tt5*tt6
tt56 = tt19**2
tt57 = 1.0E+0*tt21*tt19*tt5-1.0E+0*tt21*tt19*tt5*tt6
tt58 = tt21**2
hes(1,1) = 1.0E+0*tt2*tt5-1.0E+0*tt2*tt5*tt6
hes(1,2) = tt8
hes(1,3) = tt10
hes(1,4) = tt12
hes(1,5) = tt15
hes(1,6) = tt17
hes(1,7) = tt18
hes(1,8) = tt20
hes(1,9) = tt22
hes(2,1) = tt8
hes(2,2) = 1.0E+0*tt23*tt5-1.0E+0*tt23*tt5*tt6
hes(2,3) = tt24
hes(2,4) = tt25
hes(2,5) = tt26
hes(2,6) = tt27
hes(2,7) = tt28
hes(2,8) = tt29
hes(2,9) = tt30
hes(3,1) = tt10
hes(3,2) = tt24
hes(3,3) = 1.0E+0*tt31*tt5-1.0E+0*tt31*tt5*tt6
hes(3,4) = tt32
hes(3,5) = tt33
hes(3,6) = tt34
hes(3,7) = tt35
hes(3,8) = tt36
hes(3,9) = tt37
hes(4,1) = tt12
hes(4,2) = tt25
hes(4,3) = tt32
hes(4,4) = 1.0E+0*tt38*tt5-1.0E+0*tt38*tt5*tt6
hes(4,5) = tt39
hes(4,6) = tt40
hes(4,7) = tt41
hes(4,8) = tt42
hes(4,9) = tt43
hes(5,1) = tt15
hes(5,2) = tt26
hes(5,3) = tt33
hes(5,4) = tt39
hes(5,5) = 1.0E+0*tt44*tt5-1.0E+0*tt44*tt5*tt6
hes(5,6) = tt45
hes(5,7) = tt46
hes(5,8) = tt47
hes(5,9) = tt48
hes(6,1) = tt17
hes(6,2) = tt27
hes(6,3) = tt34
hes(6,4) = tt40
hes(6,5) = tt45
hes(6,6) = 1.0E+0*tt49*tt5-1.0E+0*tt49*tt5*tt6
hes(6,7) = tt50
hes(6,8) = tt51
hes(6,9) = tt52
hes(7,1) = tt18
hes(7,2) = tt28
hes(7,3) = tt35
hes(7,4) = tt41
hes(7,5) = tt46
hes(7,6) = tt50
hes(7,7) = 1.0E+0*tt53*tt5-1.0E+0*tt53*tt5*tt6
hes(7,8) = tt54
hes(7,9) = tt55
hes(8,1) = tt20
hes(8,2) = tt29
hes(8,3) = tt36
hes(8,4) = tt42
hes(8,5) = tt47
hes(8,6) = tt51
hes(8,7) = tt54
hes(8,8) = 1.0E+0*tt56*tt5-1.0E+0*tt56*tt5*tt6
hes(8,9) = tt57
hes(9,1) = tt22
hes(9,2) = tt30
hes(9,3) = tt37
hes(9,4) = tt43
hes(9,5) = tt48
hes(9,6) = tt52
hes(9,7) = tt55
hes(9,8) = tt57
hes(9,9) = 1.0E+0*tt58*tt5-1.0E+0*tt58*tt5*tt6
END
SUBROUTINE &
&bonet08_neohookean_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)&
&**2+F(2,1)**2+F(1,3)**2+F(1,2)**2+F(1,1)**2-3)-log(F(1,1)*(F(2,2)&
&*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3&
&)*(F(2,1)*F(3,2)-F(2,2)*F(3,1)))
END
SUBROUTINE &
&bonet08_neohookean_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = 1/(F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*t&
&t2)
jac(1,1) = 1.0E+0*F(1,1)-tt1*tt3
jac(1,2) = 1.0E+0*F(2,1)-(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*F(3,1)-(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*F(1,2)-(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*F(2,2)-(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*F(3,2)-(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*F(1,3)-tt2*tt3
jac(1,8) = 1.0E+0*F(2,3)-(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*F(3,3)-(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&bonet08_neohookean_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2
tt4 = 1/tt3**2
tt5 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt6 = tt5*tt1*tt4
tt7 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt8 = tt7*tt1*tt4
tt9 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt10 = tt9*tt1*tt4
tt11 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt12 = 1/tt3
tt13 = tt11*tt1*tt4-F(3,3)*tt12
tt14 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt15 = F(2,3)*tt12+tt14*tt1*tt4
tt16 = tt2*tt1*tt4
tt17 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt18 = F(3,2)*tt12+tt17*tt1*tt4
tt19 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt20 = tt19*tt1*tt4-F(2,2)*tt12
tt21 = tt7*tt5*tt4
tt22 = F(3,3)*tt12+tt5*tt9*tt4
tt23 = tt11*tt5*tt4
tt24 = tt14*tt5*tt4-F(1,3)*tt12
tt25 = tt2*tt5*tt4-F(3,2)*tt12
tt26 = tt17*tt5*tt4
tt27 = F(1,2)*tt12+tt19*tt5*tt4
tt28 = tt7*tt9*tt4-F(2,3)*tt12
tt29 = F(1,3)*tt12+tt7*tt11*tt4
tt30 = tt14*tt7*tt4
tt31 = F(2,2)*tt12+tt7*tt2*tt4
tt32 = tt7*tt17*tt4-F(1,2)*tt12
tt33 = tt19*tt7*tt4
tt34 = tt11*tt9*tt4
tt35 = tt14*tt9*tt4
tt36 = tt2*tt9*tt4
tt37 = tt17*tt9*tt4-F(3,1)*tt12
tt38 = F(2,1)*tt12+tt19*tt9*tt4
tt39 = tt14*tt11*tt4
tt40 = F(3,1)*tt12+tt2*tt11*tt4
tt41 = tt17*tt11*tt4
tt42 = tt19*tt11*tt4-F(1,1)*tt12
tt43 = tt14*tt2*tt4-F(2,1)*tt12
tt44 = F(1,1)*tt12+tt14*tt17*tt4
tt45 = tt19*tt14*tt4
tt46 = tt17*tt2*tt4
tt47 = tt19*tt2*tt4
tt48 = tt19*tt17*tt4
hes(1,1) = tt1**2*tt4+1.0E+0
hes(1,2) = tt6
hes(1,3) = tt8
hes(1,4) = tt10
hes(1,5) = tt13
hes(1,6) = tt15
hes(1,7) = tt16
hes(1,8) = tt18
hes(1,9) = tt20
hes(2,1) = tt6
hes(2,2) = tt5**2*tt4+1.0E+0
hes(2,3) = tt21
hes(2,4) = tt22
hes(2,5) = tt23
hes(2,6) = tt24
hes(2,7) = tt25
hes(2,8) = tt26
hes(2,9) = tt27
hes(3,1) = tt8
hes(3,2) = tt21
hes(3,3) = tt7**2*tt4+1.0E+0
hes(3,4) = tt28
hes(3,5) = tt29
hes(3,6) = tt30
hes(3,7) = tt31
hes(3,8) = tt32
hes(3,9) = tt33
hes(4,1) = tt10
hes(4,2) = tt22
hes(4,3) = tt28
hes(4,4) = tt9**2*tt4+1.0E+0
hes(4,5) = tt34
hes(4,6) = tt35
hes(4,7) = tt36
hes(4,8) = tt37
hes(4,9) = tt38
hes(5,1) = tt13
hes(5,2) = tt23
hes(5,3) = tt29
hes(5,4) = tt34
hes(5,5) = tt11**2*tt4+1.0E+0
hes(5,6) = tt39
hes(5,7) = tt40
hes(5,8) = tt41
hes(5,9) = tt42
hes(6,1) = tt15
hes(6,2) = tt24
hes(6,3) = tt30
hes(6,4) = tt35
hes(6,5) = tt39
hes(6,6) = tt14**2*tt4+1.0E+0
hes(6,7) = tt43
hes(6,8) = tt44
hes(6,9) = tt45
hes(7,1) = tt16
hes(7,2) = tt25
hes(7,3) = tt31
hes(7,4) = tt36
hes(7,5) = tt40
hes(7,6) = tt43
hes(7,7) = tt2**2*tt4+1.0E+0
hes(7,8) = tt46
hes(7,9) = tt47
hes(8,1) = tt18
hes(8,2) = tt26
hes(8,3) = tt32
hes(8,4) = tt37
hes(8,5) = tt41
hes(8,6) = tt44
hes(8,7) = tt46
hes(8,8) = tt17**2*tt4+1.0E+0
hes(8,9) = tt48
hes(9,1) = tt20
hes(9,2) = tt27
hes(9,3) = tt33
hes(9,4) = tt38
hes(9,5) = tt42
hes(9,6) = tt45
hes(9,7) = tt47
hes(9,8) = tt48
hes(9,9) = tt19**2*tt4+1.0E+0
END
SUBROUTINE &
&ogden97_neohookean_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F&
&(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-&
&1)**2
END
SUBROUTINE &
&ogden97_neohookean_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
jac(1,1) = 1.0E+0*tt1*tt3
jac(1,2) = 1.0E+0*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*tt2*tt3
jac(1,8) = 1.0E+0*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&ogden97_neohookean_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt3 = 1.0E+0*tt2*tt1
tt4 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt5 = 1.0E+0*tt4*tt1
tt6 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt7 = 1.0E+0*tt6*tt1
tt8 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt9 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt10 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt9&
&-1
tt11 = 1.0E+0*F(3,3)*tt10+1.0E+0*tt8*tt1
tt12 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt13 = 1.0E+0*tt12*tt1-1.0E+0*F(2,3)*tt10
tt14 = 1.0E+0*tt9*tt1
tt15 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt16 = 1.0E+0*tt15*tt1-1.0E+0*F(3,2)*tt10
tt17 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt18 = 1.0E+0*F(2,2)*tt10+1.0E+0*tt17*tt1
tt19 = 1.0E+0*tt4*tt2
tt20 = 1.0E+0*tt2*tt6-1.0E+0*F(3,3)*tt10
tt21 = 1.0E+0*tt8*tt2
tt22 = 1.0E+0*F(1,3)*tt10+1.0E+0*tt12*tt2
tt23 = 1.0E+0*F(3,2)*tt10+1.0E+0*tt9*tt2
tt24 = 1.0E+0*tt15*tt2
tt25 = 1.0E+0*tt17*tt2-1.0E+0*F(1,2)*tt10
tt26 = 1.0E+0*F(2,3)*tt10+1.0E+0*tt4*tt6
tt27 = 1.0E+0*tt4*tt8-1.0E+0*F(1,3)*tt10
tt28 = 1.0E+0*tt12*tt4
tt29 = 1.0E+0*tt4*tt9-1.0E+0*F(2,2)*tt10
tt30 = 1.0E+0*F(1,2)*tt10+1.0E+0*tt4*tt15
tt31 = 1.0E+0*tt17*tt4
tt32 = 1.0E+0*tt8*tt6
tt33 = 1.0E+0*tt12*tt6
tt34 = 1.0E+0*tt9*tt6
tt35 = 1.0E+0*F(3,1)*tt10+1.0E+0*tt15*tt6
tt36 = 1.0E+0*tt17*tt6-1.0E+0*F(2,1)*tt10
tt37 = 1.0E+0*tt12*tt8
tt38 = 1.0E+0*tt9*tt8-1.0E+0*F(3,1)*tt10
tt39 = 1.0E+0*tt15*tt8
tt40 = 1.0E+0*F(1,1)*tt10+1.0E+0*tt17*tt8
tt41 = 1.0E+0*F(2,1)*tt10+1.0E+0*tt12*tt9
tt42 = 1.0E+0*tt12*tt15-1.0E+0*F(1,1)*tt10
tt43 = 1.0E+0*tt17*tt12
tt44 = 1.0E+0*tt15*tt9
tt45 = 1.0E+0*tt17*tt9
tt46 = 1.0E+0*tt17*tt15
hes(1,1) = 1.0E+0*tt1**2
hes(1,2) = tt3
hes(1,3) = tt5
hes(1,4) = tt7
hes(1,5) = tt11
hes(1,6) = tt13
hes(1,7) = tt14
hes(1,8) = tt16
hes(1,9) = tt18
hes(2,1) = tt3
hes(2,2) = 1.0E+0*tt2**2
hes(2,3) = tt19
hes(2,4) = tt20
hes(2,5) = tt21
hes(2,6) = tt22
hes(2,7) = tt23
hes(2,8) = tt24
hes(2,9) = tt25
hes(3,1) = tt5
hes(3,2) = tt19
hes(3,3) = 1.0E+0*tt4**2
hes(3,4) = tt26
hes(3,5) = tt27
hes(3,6) = tt28
hes(3,7) = tt29
hes(3,8) = tt30
hes(3,9) = tt31
hes(4,1) = tt7
hes(4,2) = tt20
hes(4,3) = tt26
hes(4,4) = 1.0E+0*tt6**2
hes(4,5) = tt32
hes(4,6) = tt33
hes(4,7) = tt34
hes(4,8) = tt35
hes(4,9) = tt36
hes(5,1) = tt11
hes(5,2) = tt21
hes(5,3) = tt27
hes(5,4) = tt32
hes(5,5) = 1.0E+0*tt8**2
hes(5,6) = tt37
hes(5,7) = tt38
hes(5,8) = tt39
hes(5,9) = tt40
hes(6,1) = tt13
hes(6,2) = tt22
hes(6,3) = tt28
hes(6,4) = tt33
hes(6,5) = tt37
hes(6,6) = 1.0E+0*tt12**2
hes(6,7) = tt41
hes(6,8) = tt42
hes(6,9) = tt43
hes(7,1) = tt14
hes(7,2) = tt23
hes(7,3) = tt29
hes(7,4) = tt34
hes(7,5) = tt38
hes(7,6) = tt41
hes(7,7) = 1.0E+0*tt9**2
hes(7,8) = tt44
hes(7,9) = tt45
hes(8,1) = tt16
hes(8,2) = tt24
hes(8,3) = tt30
hes(8,4) = tt35
hes(8,5) = tt39
hes(8,6) = tt42
hes(8,7) = tt44
hes(8,8) = 1.0E+0*tt15**2
hes(8,9) = tt46
hes(9,1) = tt18
hes(9,2) = tt25
hes(9,3) = tt31
hes(9,4) = tt36
hes(9,5) = tt40
hes(9,6) = tt43
hes(9,7) = tt45
hes(9,8) = tt46
hes(9,9) = 1.0E+0*tt17**2
END
SUBROUTINE &
&ogden97_neohookean_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)&
&**2+F(2,1)**2+F(1,3)**2+F(1,2)**2+F(1,1)**2-3)-log(F(1,1)*(F(2,2)&
&*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3&
&)*(F(2,1)*F(3,2)-F(2,2)*F(3,1)))
END
SUBROUTINE &
&ogden97_neohookean_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = 1/(F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*t&
&t2)
jac(1,1) = 1.0E+0*F(1,1)-tt1*tt3
jac(1,2) = 1.0E+0*F(2,1)-(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*F(3,1)-(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*F(1,2)-(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*F(2,2)-(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*F(3,2)-(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*F(1,3)-tt2*tt3
jac(1,8) = 1.0E+0*F(2,3)-(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*F(3,3)-(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&ogden97_neohookean_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2
tt4 = 1/tt3**2
tt5 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt6 = tt5*tt1*tt4
tt7 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt8 = tt7*tt1*tt4
tt9 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt10 = tt9*tt1*tt4
tt11 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt12 = 1/tt3
tt13 = tt11*tt1*tt4-F(3,3)*tt12
tt14 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt15 = F(2,3)*tt12+tt14*tt1*tt4
tt16 = tt2*tt1*tt4
tt17 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt18 = F(3,2)*tt12+tt17*tt1*tt4
tt19 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt20 = tt19*tt1*tt4-F(2,2)*tt12
tt21 = tt7*tt5*tt4
tt22 = F(3,3)*tt12+tt5*tt9*tt4
tt23 = tt11*tt5*tt4
tt24 = tt14*tt5*tt4-F(1,3)*tt12
tt25 = tt2*tt5*tt4-F(3,2)*tt12
tt26 = tt17*tt5*tt4
tt27 = F(1,2)*tt12+tt19*tt5*tt4
tt28 = tt7*tt9*tt4-F(2,3)*tt12
tt29 = F(1,3)*tt12+tt7*tt11*tt4
tt30 = tt14*tt7*tt4
tt31 = F(2,2)*tt12+tt7*tt2*tt4
tt32 = tt7*tt17*tt4-F(1,2)*tt12
tt33 = tt19*tt7*tt4
tt34 = tt11*tt9*tt4
tt35 = tt14*tt9*tt4
tt36 = tt2*tt9*tt4
tt37 = tt17*tt9*tt4-F(3,1)*tt12
tt38 = F(2,1)*tt12+tt19*tt9*tt4
tt39 = tt14*tt11*tt4
tt40 = F(3,1)*tt12+tt2*tt11*tt4
tt41 = tt17*tt11*tt4
tt42 = tt19*tt11*tt4-F(1,1)*tt12
tt43 = tt14*tt2*tt4-F(2,1)*tt12
tt44 = F(1,1)*tt12+tt14*tt17*tt4
tt45 = tt19*tt14*tt4
tt46 = tt17*tt2*tt4
tt47 = tt19*tt2*tt4
tt48 = tt19*tt17*tt4
hes(1,1) = tt1**2*tt4+1.0E+0
hes(1,2) = tt6
hes(1,3) = tt8
hes(1,4) = tt10
hes(1,5) = tt13
hes(1,6) = tt15
hes(1,7) = tt16
hes(1,8) = tt18
hes(1,9) = tt20
hes(2,1) = tt6
hes(2,2) = tt5**2*tt4+1.0E+0
hes(2,3) = tt21
hes(2,4) = tt22
hes(2,5) = tt23
hes(2,6) = tt24
hes(2,7) = tt25
hes(2,8) = tt26
hes(2,9) = tt27
hes(3,1) = tt8
hes(3,2) = tt21
hes(3,3) = tt7**2*tt4+1.0E+0
hes(3,4) = tt28
hes(3,5) = tt29
hes(3,6) = tt30
hes(3,7) = tt31
hes(3,8) = tt32
hes(3,9) = tt33
hes(4,1) = tt10
hes(4,2) = tt22
hes(4,3) = tt28
hes(4,4) = tt9**2*tt4+1.0E+0
hes(4,5) = tt34
hes(4,6) = tt35
hes(4,7) = tt36
hes(4,8) = tt37
hes(4,9) = tt38
hes(5,1) = tt13
hes(5,2) = tt23
hes(5,3) = tt29
hes(5,4) = tt34
hes(5,5) = tt11**2*tt4+1.0E+0
hes(5,6) = tt39
hes(5,7) = tt40
hes(5,8) = tt41
hes(5,9) = tt42
hes(6,1) = tt15
hes(6,2) = tt24
hes(6,3) = tt30
hes(6,4) = tt35
hes(6,5) = tt39
hes(6,6) = tt14**2*tt4+1.0E+0
hes(6,7) = tt43
hes(6,8) = tt44
hes(6,9) = tt45
hes(7,1) = tt16
hes(7,2) = tt25
hes(7,3) = tt31
hes(7,4) = tt36
hes(7,5) = tt40
hes(7,6) = tt43
hes(7,7) = tt2**2*tt4+1.0E+0
hes(7,8) = tt46
hes(7,9) = tt47
hes(8,1) = tt18
hes(8,2) = tt26
hes(8,3) = tt32
hes(8,4) = tt37
hes(8,5) = tt41
hes(8,6) = tt44
hes(8,7) = tt46
hes(8,8) = tt17**2*tt4+1.0E+0
hes(8,9) = tt48
hes(9,1) = tt20
hes(9,2) = tt27
hes(9,3) = tt33
hes(9,4) = tt38
hes(9,5) = tt42
hes(9,6) = tt45
hes(9,7) = tt47
hes(9,8) = tt48
hes(9,9) = tt19**2*tt4+1.0E+0
END
SUBROUTINE &
&bower09_neohookean_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F&
&(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-&
&1)**2
END
SUBROUTINE &
&bower09_neohookean_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
jac(1,1) = 1.0E+0*tt1*tt3
jac(1,2) = 1.0E+0*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*tt2*tt3
jac(1,8) = 1.0E+0*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&bower09_neohookean_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt3 = 1.0E+0*tt2*tt1
tt4 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt5 = 1.0E+0*tt4*tt1
tt6 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt7 = 1.0E+0*tt6*tt1
tt8 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt9 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt10 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt9&
&-1
tt11 = 1.0E+0*F(3,3)*tt10+1.0E+0*tt8*tt1
tt12 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt13 = 1.0E+0*tt12*tt1-1.0E+0*F(2,3)*tt10
tt14 = 1.0E+0*tt9*tt1
tt15 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt16 = 1.0E+0*tt15*tt1-1.0E+0*F(3,2)*tt10
tt17 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt18 = 1.0E+0*F(2,2)*tt10+1.0E+0*tt17*tt1
tt19 = 1.0E+0*tt4*tt2
tt20 = 1.0E+0*tt2*tt6-1.0E+0*F(3,3)*tt10
tt21 = 1.0E+0*tt8*tt2
tt22 = 1.0E+0*F(1,3)*tt10+1.0E+0*tt12*tt2
tt23 = 1.0E+0*F(3,2)*tt10+1.0E+0*tt9*tt2
tt24 = 1.0E+0*tt15*tt2
tt25 = 1.0E+0*tt17*tt2-1.0E+0*F(1,2)*tt10
tt26 = 1.0E+0*F(2,3)*tt10+1.0E+0*tt4*tt6
tt27 = 1.0E+0*tt4*tt8-1.0E+0*F(1,3)*tt10
tt28 = 1.0E+0*tt12*tt4
tt29 = 1.0E+0*tt4*tt9-1.0E+0*F(2,2)*tt10
tt30 = 1.0E+0*F(1,2)*tt10+1.0E+0*tt4*tt15
tt31 = 1.0E+0*tt17*tt4
tt32 = 1.0E+0*tt8*tt6
tt33 = 1.0E+0*tt12*tt6
tt34 = 1.0E+0*tt9*tt6
tt35 = 1.0E+0*F(3,1)*tt10+1.0E+0*tt15*tt6
tt36 = 1.0E+0*tt17*tt6-1.0E+0*F(2,1)*tt10
tt37 = 1.0E+0*tt12*tt8
tt38 = 1.0E+0*tt9*tt8-1.0E+0*F(3,1)*tt10
tt39 = 1.0E+0*tt15*tt8
tt40 = 1.0E+0*F(1,1)*tt10+1.0E+0*tt17*tt8
tt41 = 1.0E+0*F(2,1)*tt10+1.0E+0*tt12*tt9
tt42 = 1.0E+0*tt12*tt15-1.0E+0*F(1,1)*tt10
tt43 = 1.0E+0*tt17*tt12
tt44 = 1.0E+0*tt15*tt9
tt45 = 1.0E+0*tt17*tt9
tt46 = 1.0E+0*tt17*tt15
hes(1,1) = 1.0E+0*tt1**2
hes(1,2) = tt3
hes(1,3) = tt5
hes(1,4) = tt7
hes(1,5) = tt11
hes(1,6) = tt13
hes(1,7) = tt14
hes(1,8) = tt16
hes(1,9) = tt18
hes(2,1) = tt3
hes(2,2) = 1.0E+0*tt2**2
hes(2,3) = tt19
hes(2,4) = tt20
hes(2,5) = tt21
hes(2,6) = tt22
hes(2,7) = tt23
hes(2,8) = tt24
hes(2,9) = tt25
hes(3,1) = tt5
hes(3,2) = tt19
hes(3,3) = 1.0E+0*tt4**2
hes(3,4) = tt26
hes(3,5) = tt27
hes(3,6) = tt28
hes(3,7) = tt29
hes(3,8) = tt30
hes(3,9) = tt31
hes(4,1) = tt7
hes(4,2) = tt20
hes(4,3) = tt26
hes(4,4) = 1.0E+0*tt6**2
hes(4,5) = tt32
hes(4,6) = tt33
hes(4,7) = tt34
hes(4,8) = tt35
hes(4,9) = tt36
hes(5,1) = tt11
hes(5,2) = tt21
hes(5,3) = tt27
hes(5,4) = tt32
hes(5,5) = 1.0E+0*tt8**2
hes(5,6) = tt37
hes(5,7) = tt38
hes(5,8) = tt39
hes(5,9) = tt40
hes(6,1) = tt13
hes(6,2) = tt22
hes(6,3) = tt28
hes(6,4) = tt33
hes(6,5) = tt37
hes(6,6) = 1.0E+0*tt12**2
hes(6,7) = tt41
hes(6,8) = tt42
hes(6,9) = tt43
hes(7,1) = tt14
hes(7,2) = tt23
hes(7,3) = tt29
hes(7,4) = tt34
hes(7,5) = tt38
hes(7,6) = tt41
hes(7,7) = 1.0E+0*tt9**2
hes(7,8) = tt44
hes(7,9) = tt45
hes(8,1) = tt16
hes(8,2) = tt24
hes(8,3) = tt30
hes(8,4) = tt35
hes(8,5) = tt39
hes(8,6) = tt42
hes(8,7) = tt44
hes(8,8) = 1.0E+0*tt15**2
hes(8,9) = tt46
hes(9,1) = tt18
hes(9,2) = tt25
hes(9,3) = tt31
hes(9,4) = tt36
hes(9,5) = tt40
hes(9,6) = tt43
hes(9,7) = tt45
hes(9,8) = tt46
hes(9,9) = 1.0E+0*tt17**2
END
SUBROUTINE &
&bower09_neohookean_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*((F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(&
&F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))&
&)**((-2.0E+0)/3.0E+0)*(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(&
&2,2)**2+F(2,1)**2+F(1,3)**2+F(1,2)**2+F(1,1)**2)-3)
END
SUBROUTINE &
&bower09_neohookean_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2
tt4 = tt3**((-5.0E+0)/3.0E+0)
tt5 = F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2&
&+F(1,3)**2+F(1,2)**2+F(1,1)**2
tt6 = tt3**((-2.0E+0)/3.0E+0)
jac(1,1) = 5.0E-1*(2*F(1,1)*tt6+((-2.0E+0)*tt1*tt4*tt5)/3.0E+0)
jac(1,2) = 5.0E-1*(2*F(2,1)*tt6+((-2.0E+0)*(F(1,3)*F(3,2)-F(1,2)*&
&F(3,3))*tt4*tt5)/3.0E+0)
jac(1,3) = 5.0E-1*(2*F(3,1)*tt6+((-2.0E+0)*(F(1,2)*F(2,3)-F(1,3)*&
&F(2,2))*tt4*tt5)/3.0E+0)
jac(1,4) = 5.0E-1*(2*F(1,2)*tt6+((-2.0E+0)*(F(2,3)*F(3,1)-F(2,1)*&
&F(3,3))*tt4*tt5)/3.0E+0)
jac(1,5) = 5.0E-1*(2*F(2,2)*tt6+((-2.0E+0)*(F(1,1)*F(3,3)-F(1,3)*&
&F(3,1))*tt4*tt5)/3.0E+0)
jac(1,6) = 5.0E-1*(2*F(3,2)*tt6+((-2.0E+0)*(F(1,3)*F(2,1)-F(1,1)*&
&F(2,3))*tt4*tt5)/3.0E+0)
jac(1,7) = 5.0E-1*(2*F(1,3)*tt6+((-2.0E+0)*tt2*tt4*tt5)/3.0E+0)
jac(1,8) = 5.0E-1*(2*F(2,3)*tt6+((-2.0E+0)*(F(1,2)*F(3,1)-F(1,1)*&
&F(3,2))*tt4*tt5)/3.0E+0)
jac(1,9) = 5.0E-1*(2*F(3,3)*tt6+((-2.0E+0)*(F(1,1)*F(2,2)-F(1,2)*&
&F(2,1))*tt4*tt5)/3.0E+0)
END
SUBROUTINE &
&bower09_neohookean_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2
tt4 = tt3**((-8.0E+0)/3.0E+0)
tt5 = F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)**2&
&+F(1,3)**2+F(1,2)**2+F(1,1)**2
tt6 = tt3**((-5.0E+0)/3.0E+0)
tt7 = 2/tt3**(2.0E+0/3.0E+0)
tt8 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt9 = 5.0E-1*(((-4.0E+0)*F(2,1)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1)&
&*tt8*tt6)/3.0E+0+(1.0E+1*tt8*tt1*tt4*tt5)/9.0E+0)
tt10 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt11 = 5.0E-1*(((-4.0E+0)*F(3,1)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt10*tt6)/3.0E+0+(1.0E+1*tt10*tt1*tt4*tt5)/9.0E+0)
tt12 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt13 = 5.0E-1*(((-4.0E+0)*F(1,2)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt12*tt6)/3.0E+0+(1.0E+1*tt12*tt1*tt4*tt5)/9.0E+0)
tt14 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt15 = 5.0E-1*(((-4.0E+0)*F(2,2)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt14*tt6)/3.0E+0+((-2.0E+0)*F(3,3)*tt6*tt5)/3.0E+0+(1.0E+1*tt14&
&*tt1*tt4*tt5)/9.0E+0)
tt16 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt17 = 5.0E-1*(((-4.0E+0)*F(3,2)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt16*tt6)/3.0E+0+(2.0E+0*F(2,3)*tt6*tt5)/3.0E+0+(1.0E+1*tt16*tt&
&1*tt4*tt5)/9.0E+0)
tt18 = 5.0E-1*(((-4.0E+0)*F(1,3)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt2*tt6)/3.0E+0+(1.0E+1*tt2*tt1*tt4*tt5)/9.0E+0)
tt19 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt20 = 5.0E-1*(((-4.0E+0)*F(2,3)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt19*tt6)/3.0E+0+(2.0E+0*F(3,2)*tt6*tt5)/3.0E+0+(1.0E+1*tt19*tt&
&1*tt4*tt5)/9.0E+0)
tt21 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt22 = 5.0E-1*(((-4.0E+0)*F(3,3)*tt1*tt6)/3.0E+0+((-4.0E+0)*F(1,1&
&)*tt21*tt6)/3.0E+0+((-2.0E+0)*F(2,2)*tt6*tt5)/3.0E+0+(1.0E+1*tt21&
&*tt1*tt4*tt5)/9.0E+0)
tt23 = 5.0E-1*(((-4.0E+0)*F(3,1)*tt8*tt6)/3.0E+0+((-4.0E+0)*F(2,1&
&)*tt10*tt6)/3.0E+0+(1.0E+1*tt10*tt8*tt4*tt5)/9.0E+0)
tt24 = 5.0E-1*(((-4.0E+0)*F(2,1)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt8*tt6)/3.0E+0+(2.0E+0*F(3,3)*tt6*tt5)/3.0E+0+(1.0E+1*tt8*tt1&
&2*tt4*tt5)/9.0E+0)
tt25 = 5.0E-1*(((-4.0E+0)*F(2,2)*tt8*tt6)/3.0E+0+((-4.0E+0)*F(2,1&
&)*tt14*tt6)/3.0E+0+(1.0E+1*tt14*tt8*tt4*tt5)/9.0E+0)
tt26 = 5.0E-1*(((-4.0E+0)*F(3,2)*tt8*tt6)/3.0E+0+((-4.0E+0)*F(2,1&
&)*tt16*tt6)/3.0E+0+((-2.0E+0)*F(1,3)*tt6*tt5)/3.0E+0+(1.0E+1*tt16&
&*tt8*tt4*tt5)/9.0E+0)
tt27 = 5.0E-1*(((-4.0E+0)*F(1,3)*tt8*tt6)/3.0E+0+((-4.0E+0)*F(2,1&
&)*tt2*tt6)/3.0E+0+((-2.0E+0)*F(3,2)*tt6*tt5)/3.0E+0+(1.0E+1*tt2*t&
&t8*tt4*tt5)/9.0E+0)
tt28 = 5.0E-1*(((-4.0E+0)*F(2,3)*tt8*tt6)/3.0E+0+((-4.0E+0)*F(2,1&
&)*tt19*tt6)/3.0E+0+(1.0E+1*tt19*tt8*tt4*tt5)/9.0E+0)
tt29 = 5.0E-1*(((-4.0E+0)*F(3,3)*tt8*tt6)/3.0E+0+((-4.0E+0)*F(2,1&
&)*tt21*tt6)/3.0E+0+(2.0E+0*F(1,2)*tt6*tt5)/3.0E+0+(1.0E+1*tt21*tt&
&8*tt4*tt5)/9.0E+0)
tt30 = 5.0E-1*(((-4.0E+0)*F(3,1)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt10*tt6)/3.0E+0+((-2.0E+0)*F(2,3)*tt6*tt5)/3.0E+0+(1.0E+1*tt1&
&0*tt12*tt4*tt5)/9.0E+0)
tt31 = 5.0E-1*(((-4.0E+0)*F(3,1)*tt14*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&2)*tt10*tt6)/3.0E+0+(2.0E+0*F(1,3)*tt6*tt5)/3.0E+0+(1.0E+1*tt10*t&
&t14*tt4*tt5)/9.0E+0)
tt32 = 5.0E-1*(((-4.0E+0)*tt10*F(3,2)*tt6)/3.0E+0+((-4.0E+0)*tt16&
&*F(3,1)*tt6)/3.0E+0+(1.0E+1*tt16*tt10*tt4*tt5)/9.0E+0)
tt33 = 5.0E-1*(((-4.0E+0)*F(3,1)*tt2*tt6)/3.0E+0+((-4.0E+0)*F(1,3&
&)*tt10*tt6)/3.0E+0+(2.0E+0*F(2,2)*tt6*tt5)/3.0E+0+(1.0E+1*tt10*tt&
&2*tt4*tt5)/9.0E+0)
tt34 = 5.0E-1*(((-4.0E+0)*F(3,1)*tt19*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&3)*tt10*tt6)/3.0E+0+((-2.0E+0)*F(1,2)*tt6*tt5)/3.0E+0+(1.0E+1*tt1&
&0*tt19*tt4*tt5)/9.0E+0)
tt35 = 5.0E-1*(((-4.0E+0)*tt10*F(3,3)*tt6)/3.0E+0+((-4.0E+0)*tt21&
&*F(3,1)*tt6)/3.0E+0+(1.0E+1*tt21*tt10*tt4*tt5)/9.0E+0)
tt36 = 5.0E-1*(((-4.0E+0)*F(2,2)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt14*tt6)/3.0E+0+(1.0E+1*tt14*tt12*tt4*tt5)/9.0E+0)
tt37 = 5.0E-1*(((-4.0E+0)*F(3,2)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt16*tt6)/3.0E+0+(1.0E+1*tt16*tt12*tt4*tt5)/9.0E+0)
tt38 = 5.0E-1*(((-4.0E+0)*F(1,3)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt2*tt6)/3.0E+0+(1.0E+1*tt2*tt12*tt4*tt5)/9.0E+0)
tt39 = 5.0E-1*(((-4.0E+0)*F(2,3)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt19*tt6)/3.0E+0+((-2.0E+0)*F(3,1)*tt6*tt5)/3.0E+0+(1.0E+1*tt1&
&9*tt12*tt4*tt5)/9.0E+0)
tt40 = 5.0E-1*(((-4.0E+0)*F(3,3)*tt12*tt6)/3.0E+0+((-4.0E+0)*F(1,&
&2)*tt21*tt6)/3.0E+0+(2.0E+0*F(2,1)*tt6*tt5)/3.0E+0+(1.0E+1*tt21*t&
&t12*tt4*tt5)/9.0E+0)
tt41 = 5.0E-1*(((-4.0E+0)*F(3,2)*tt14*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&2)*tt16*tt6)/3.0E+0+(1.0E+1*tt16*tt14*tt4*tt5)/9.0E+0)
tt42 = 5.0E-1*(((-4.0E+0)*F(1,3)*tt14*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&2)*tt2*tt6)/3.0E+0+(2.0E+0*F(3,1)*tt6*tt5)/3.0E+0+(1.0E+1*tt2*tt1&
&4*tt4*tt5)/9.0E+0)
tt43 = 5.0E-1*(((-4.0E+0)*F(2,3)*tt14*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&2)*tt19*tt6)/3.0E+0+(1.0E+1*tt19*tt14*tt4*tt5)/9.0E+0)
tt44 = 5.0E-1*(((-4.0E+0)*F(3,3)*tt14*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&2)*tt21*tt6)/3.0E+0+((-2.0E+0)*F(1,1)*tt6*tt5)/3.0E+0+(1.0E+1*tt2&
&1*tt14*tt4*tt5)/9.0E+0)
tt45 = 5.0E-1*(((-4.0E+0)*F(3,2)*tt2*tt6)/3.0E+0+((-4.0E+0)*F(1,3&
&)*tt16*tt6)/3.0E+0+((-2.0E+0)*F(2,1)*tt6*tt5)/3.0E+0+(1.0E+1*tt16&
&*tt2*tt4*tt5)/9.0E+0)
tt46 = 5.0E-1*(((-4.0E+0)*F(3,2)*tt19*tt6)/3.0E+0+((-4.0E+0)*F(2,&
&3)*tt16*tt6)/3.0E+0+(2.0E+0*F(1,1)*tt6*tt5)/3.0E+0+(1.0E+1*tt16*t&
&t19*tt4*tt5)/9.0E+0)
tt47 = 5.0E-1*(((-4.0E+0)*tt16*F(3,3)*tt6)/3.0E+0+((-4.0E+0)*tt21&
&*F(3,2)*tt6)/3.0E+0+(1.0E+1*tt21*tt16*tt4*tt5)/9.0E+0)
tt48 = 5.0E-1*(((-4.0E+0)*F(2,3)*tt2*tt6)/3.0E+0+((-4.0E+0)*F(1,3&
&)*tt19*tt6)/3.0E+0+(1.0E+1*tt19*tt2*tt4*tt5)/9.0E+0)
tt49 = 5.0E-1*(((-4.0E+0)*tt2*F(3,3)*tt6)/3.0E+0+((-4.0E+0)*F(1,3&
&)*tt21*tt6)/3.0E+0+(1.0E+1*tt21*tt2*tt4*tt5)/9.0E+0)
tt50 = 5.0E-1*(((-4.0E+0)*tt19*F(3,3)*tt6)/3.0E+0+((-4.0E+0)*tt21&
&*F(2,3)*tt6)/3.0E+0+(1.0E+1*tt21*tt19*tt4*tt5)/9.0E+0)
hes(1,1) = 5.0E-1*(tt7+((-8.0E+0)*F(1,1)*tt1*tt6)/3.0E+0+(1.0E+1*&
&tt1**2*tt4*tt5)/9.0E+0)
hes(1,2) = tt9
hes(1,3) = tt11
hes(1,4) = tt13
hes(1,5) = tt15
hes(1,6) = tt17
hes(1,7) = tt18
hes(1,8) = tt20
hes(1,9) = tt22
hes(2,1) = tt9
hes(2,2) = 5.0E-1*(tt7+((-8.0E+0)*F(2,1)*tt8*tt6)/3.0E+0+(1.0E+1*&
&tt8**2*tt4*tt5)/9.0E+0)
hes(2,3) = tt23
hes(2,4) = tt24
hes(2,5) = tt25
hes(2,6) = tt26
hes(2,7) = tt27
hes(2,8) = tt28
hes(2,9) = tt29
hes(3,1) = tt11
hes(3,2) = tt23
hes(3,3) = 5.0E-1*(tt7+((-8.0E+0)*tt10*F(3,1)*tt6)/3.0E+0+(1.0E+1&
&*tt10**2*tt4*tt5)/9.0E+0)
hes(3,4) = tt30
hes(3,5) = tt31
hes(3,6) = tt32
hes(3,7) = tt33
hes(3,8) = tt34
hes(3,9) = tt35
hes(4,1) = tt13
hes(4,2) = tt24
hes(4,3) = tt30
hes(4,4) = 5.0E-1*(tt7+((-8.0E+0)*F(1,2)*tt12*tt6)/3.0E+0+(1.0E+1&
&*tt12**2*tt4*tt5)/9.0E+0)
hes(4,5) = tt36
hes(4,6) = tt37
hes(4,7) = tt38
hes(4,8) = tt39
hes(4,9) = tt40
hes(5,1) = tt15
hes(5,2) = tt25
hes(5,3) = tt31
hes(5,4) = tt36
hes(5,5) = 5.0E-1*(tt7+((-8.0E+0)*F(2,2)*tt14*tt6)/3.0E+0+(1.0E+1&
&*tt14**2*tt4*tt5)/9.0E+0)
hes(5,6) = tt41
hes(5,7) = tt42
hes(5,8) = tt43
hes(5,9) = tt44
hes(6,1) = tt17
hes(6,2) = tt26
hes(6,3) = tt32
hes(6,4) = tt37
hes(6,5) = tt41
hes(6,6) = 5.0E-1*(tt7+((-8.0E+0)*tt16*F(3,2)*tt6)/3.0E+0+(1.0E+1&
&*tt16**2*tt4*tt5)/9.0E+0)
hes(6,7) = tt45
hes(6,8) = tt46
hes(6,9) = tt47
hes(7,1) = tt18
hes(7,2) = tt27
hes(7,3) = tt33
hes(7,4) = tt38
hes(7,5) = tt42
hes(7,6) = tt45
hes(7,7) = 5.0E-1*(tt7+((-8.0E+0)*F(1,3)*tt2*tt6)/3.0E+0+(1.0E+1*&
&tt2**2*tt4*tt5)/9.0E+0)
hes(7,8) = tt48
hes(7,9) = tt49
hes(8,1) = tt20
hes(8,2) = tt28
hes(8,3) = tt34
hes(8,4) = tt39
hes(8,5) = tt43
hes(8,6) = tt46
hes(8,7) = tt48
hes(8,8) = 5.0E-1*(tt7+((-8.0E+0)*F(2,3)*tt19*tt6)/3.0E+0+(1.0E+1&
&*tt19**2*tt4*tt5)/9.0E+0)
hes(8,9) = tt50
hes(9,1) = tt22
hes(9,2) = tt29
hes(9,3) = tt35
hes(9,4) = tt40
hes(9,5) = tt44
hes(9,6) = tt47
hes(9,7) = tt49
hes(9,8) = tt50
hes(9,9) = 5.0E-1*(tt7+((-8.0E+0)*tt21*F(3,3)*tt6)/3.0E+0+(1.0E+1&
&*tt21**2*tt4*tt5)/9.0E+0)
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F&
&(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-&
&1)**2
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
jac(1,1) = 1.0E+0*tt1*tt3
jac(1,2) = 1.0E+0*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*tt2*tt3
jac(1,8) = 1.0E+0*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt3 = 1.0E+0*tt2*tt1
tt4 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt5 = 1.0E+0*tt4*tt1
tt6 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt7 = 1.0E+0*tt6*tt1
tt8 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt9 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt10 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt9&
&-1
tt11 = 1.0E+0*F(3,3)*tt10+1.0E+0*tt8*tt1
tt12 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt13 = 1.0E+0*tt12*tt1-1.0E+0*F(2,3)*tt10
tt14 = 1.0E+0*tt9*tt1
tt15 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt16 = 1.0E+0*tt15*tt1-1.0E+0*F(3,2)*tt10
tt17 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt18 = 1.0E+0*F(2,2)*tt10+1.0E+0*tt17*tt1
tt19 = 1.0E+0*tt4*tt2
tt20 = 1.0E+0*tt2*tt6-1.0E+0*F(3,3)*tt10
tt21 = 1.0E+0*tt8*tt2
tt22 = 1.0E+0*F(1,3)*tt10+1.0E+0*tt12*tt2
tt23 = 1.0E+0*F(3,2)*tt10+1.0E+0*tt9*tt2
tt24 = 1.0E+0*tt15*tt2
tt25 = 1.0E+0*tt17*tt2-1.0E+0*F(1,2)*tt10
tt26 = 1.0E+0*F(2,3)*tt10+1.0E+0*tt4*tt6
tt27 = 1.0E+0*tt4*tt8-1.0E+0*F(1,3)*tt10
tt28 = 1.0E+0*tt12*tt4
tt29 = 1.0E+0*tt4*tt9-1.0E+0*F(2,2)*tt10
tt30 = 1.0E+0*F(1,2)*tt10+1.0E+0*tt4*tt15
tt31 = 1.0E+0*tt17*tt4
tt32 = 1.0E+0*tt8*tt6
tt33 = 1.0E+0*tt12*tt6
tt34 = 1.0E+0*tt9*tt6
tt35 = 1.0E+0*F(3,1)*tt10+1.0E+0*tt15*tt6
tt36 = 1.0E+0*tt17*tt6-1.0E+0*F(2,1)*tt10
tt37 = 1.0E+0*tt12*tt8
tt38 = 1.0E+0*tt9*tt8-1.0E+0*F(3,1)*tt10
tt39 = 1.0E+0*tt15*tt8
tt40 = 1.0E+0*F(1,1)*tt10+1.0E+0*tt17*tt8
tt41 = 1.0E+0*F(2,1)*tt10+1.0E+0*tt12*tt9
tt42 = 1.0E+0*tt12*tt15-1.0E+0*F(1,1)*tt10
tt43 = 1.0E+0*tt17*tt12
tt44 = 1.0E+0*tt15*tt9
tt45 = 1.0E+0*tt17*tt9
tt46 = 1.0E+0*tt17*tt15
hes(1,1) = 1.0E+0*tt1**2
hes(1,2) = tt3
hes(1,3) = tt5
hes(1,4) = tt7
hes(1,5) = tt11
hes(1,6) = tt13
hes(1,7) = tt14
hes(1,8) = tt16
hes(1,9) = tt18
hes(2,1) = tt3
hes(2,2) = 1.0E+0*tt2**2
hes(2,3) = tt19
hes(2,4) = tt20
hes(2,5) = tt21
hes(2,6) = tt22
hes(2,7) = tt23
hes(2,8) = tt24
hes(2,9) = tt25
hes(3,1) = tt5
hes(3,2) = tt19
hes(3,3) = 1.0E+0*tt4**2
hes(3,4) = tt26
hes(3,5) = tt27
hes(3,6) = tt28
hes(3,7) = tt29
hes(3,8) = tt30
hes(3,9) = tt31
hes(4,1) = tt7
hes(4,2) = tt20
hes(4,3) = tt26
hes(4,4) = 1.0E+0*tt6**2
hes(4,5) = tt32
hes(4,6) = tt33
hes(4,7) = tt34
hes(4,8) = tt35
hes(4,9) = tt36
hes(5,1) = tt11
hes(5,2) = tt21
hes(5,3) = tt27
hes(5,4) = tt32
hes(5,5) = 1.0E+0*tt8**2
hes(5,6) = tt37
hes(5,7) = tt38
hes(5,8) = tt39
hes(5,9) = tt40
hes(6,1) = tt13
hes(6,2) = tt22
hes(6,3) = tt28
hes(6,4) = tt33
hes(6,5) = tt37
hes(6,6) = 1.0E+0*tt12**2
hes(6,7) = tt41
hes(6,8) = tt42
hes(6,9) = tt43
hes(7,1) = tt14
hes(7,2) = tt23
hes(7,3) = tt29
hes(7,4) = tt34
hes(7,5) = tt38
hes(7,6) = tt41
hes(7,7) = 1.0E+0*tt9**2
hes(7,8) = tt44
hes(7,9) = tt45
hes(8,1) = tt16
hes(8,2) = tt24
hes(8,3) = tt30
hes(8,4) = tt35
hes(8,5) = tt39
hes(8,6) = tt42
hes(8,7) = tt44
hes(8,8) = 1.0E+0*tt15**2
hes(8,9) = tt46
hes(9,1) = tt18
hes(9,2) = tt25
hes(9,3) = tt31
hes(9,4) = tt36
hes(9,5) = tt40
hes(9,6) = tt43
hes(9,7) = tt45
hes(9,8) = tt46
hes(9,9) = 1.0E+0*tt17**2
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)&
&**2+F(2,1)**2+F(1,3)**2+F(1,2)**2+F(1,1)**2-3)-F(1,1)*(F(2,2)*F(3&
&,3)-F(2,3)*F(3,2))+F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))-F(1,3)*(F&
&(2,1)*F(3,2)-F(2,2)*F(3,1))+1
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
jac(1,1) = (-F(2,2)*F(3,3))+F(2,3)*F(3,2)+1.0E+0*F(1,1)
jac(1,2) = F(1,2)*F(3,3)-F(1,3)*F(3,2)+1.0E+0*F(2,1)
jac(1,3) = 1.0E+0*F(3,1)-F(1,2)*F(2,3)+F(1,3)*F(2,2)
jac(1,4) = F(2,1)*F(3,3)-F(2,3)*F(3,1)+1.0E+0*F(1,2)
jac(1,5) = (-F(1,1)*F(3,3))+F(1,3)*F(3,1)+1.0E+0*F(2,2)
jac(1,6) = 1.0E+0*F(3,2)+F(1,1)*F(2,3)-F(1,3)*F(2,1)
jac(1,7) = (-F(2,1)*F(3,2))+F(2,2)*F(3,1)+1.0E+0*F(1,3)
jac(1,8) = F(1,1)*F(3,2)-F(1,2)*F(3,1)+1.0E+0*F(2,3)
jac(1,9) = 1.0E+0*F(3,3)-F(1,1)*F(2,2)+F(1,2)*F(2,1)
END
SUBROUTINE &
&pixar18_rest_stable_neohookean_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
REAL(KIND=8)  tt8
REAL(KIND=8)  tt9
tt1 = -F(3,3)
tt2 = -F(2,2)
tt3 = -F(1,3)
tt4 = -F(3,2)
tt5 = -F(2,3)
tt6 = -F(1,2)
tt7 = -F(3,1)
tt8 = -F(1,1)
tt9 = -F(2,1)
hes(1,1) = 1.0E+0
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = tt1
hes(1,6) = F(2,3)
hes(1,7) = 0
hes(1,8) = F(3,2)
hes(1,9) = tt2
hes(2,1) = 0
hes(2,2) = 1.0E+0
hes(2,3) = 0
hes(2,4) = F(3,3)
hes(2,5) = 0
hes(2,6) = tt3
hes(2,7) = tt4
hes(2,8) = 0
hes(2,9) = F(1,2)
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 1.0E+0
hes(3,4) = tt5
hes(3,5) = F(1,3)
hes(3,6) = 0
hes(3,7) = F(2,2)
hes(3,8) = tt6
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = F(3,3)
hes(4,3) = tt5
hes(4,4) = 1.0E+0
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = tt7
hes(4,9) = F(2,1)
hes(5,1) = tt1
hes(5,2) = 0
hes(5,3) = F(1,3)
hes(5,4) = 0
hes(5,5) = 1.0E+0
hes(5,6) = 0
hes(5,7) = F(3,1)
hes(5,8) = 0
hes(5,9) = tt8
hes(6,1) = F(2,3)
hes(6,2) = tt3
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 1.0E+0
hes(6,7) = tt9
hes(6,8) = F(1,1)
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = tt4
hes(7,3) = F(2,2)
hes(7,4) = 0
hes(7,5) = F(3,1)
hes(7,6) = tt9
hes(7,7) = 1.0E+0
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = F(3,2)
hes(8,2) = 0
hes(8,3) = tt6
hes(8,4) = tt7
hes(8,5) = 0
hes(8,6) = F(1,1)
hes(8,7) = 0
hes(8,8) = 1.0E+0
hes(8,9) = 0
hes(9,1) = tt2
hes(9,2) = F(1,2)
hes(9,3) = 0
hes(9,4) = F(2,1)
hes(9,5) = tt8
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 1.0E+0
END
SUBROUTINE &
&pixar18_neohookean_lam_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = 5.0E-1*(F(1,1)*(F(2,2)*F(3,3)-F(2,3)*F(3,2))-F(1,2)*(F&
&(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*(F(2,1)*F(3,2)-F(2,2)*F(3,1))-&
&1)**2
END
SUBROUTINE &
&pixar18_neohookean_lam_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2-&
&1
jac(1,1) = 1.0E+0*tt1*tt3
jac(1,2) = 1.0E+0*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt3
jac(1,3) = 1.0E+0*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt3
jac(1,4) = 1.0E+0*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt3
jac(1,5) = 1.0E+0*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt3
jac(1,6) = 1.0E+0*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt3
jac(1,7) = 1.0E+0*tt2*tt3
jac(1,8) = 1.0E+0*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt3
jac(1,9) = 1.0E+0*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt3
END
SUBROUTINE &
&pixar18_neohookean_lam_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt3 = 1.0E+0*tt2*tt1
tt4 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt5 = 1.0E+0*tt4*tt1
tt6 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt7 = 1.0E+0*tt6*tt1
tt8 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt9 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt10 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt9&
&-1
tt11 = 1.0E+0*F(3,3)*tt10+1.0E+0*tt8*tt1
tt12 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt13 = 1.0E+0*tt12*tt1-1.0E+0*F(2,3)*tt10
tt14 = 1.0E+0*tt9*tt1
tt15 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt16 = 1.0E+0*tt15*tt1-1.0E+0*F(3,2)*tt10
tt17 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt18 = 1.0E+0*F(2,2)*tt10+1.0E+0*tt17*tt1
tt19 = 1.0E+0*tt4*tt2
tt20 = 1.0E+0*tt2*tt6-1.0E+0*F(3,3)*tt10
tt21 = 1.0E+0*tt8*tt2
tt22 = 1.0E+0*F(1,3)*tt10+1.0E+0*tt12*tt2
tt23 = 1.0E+0*F(3,2)*tt10+1.0E+0*tt9*tt2
tt24 = 1.0E+0*tt15*tt2
tt25 = 1.0E+0*tt17*tt2-1.0E+0*F(1,2)*tt10
tt26 = 1.0E+0*F(2,3)*tt10+1.0E+0*tt4*tt6
tt27 = 1.0E+0*tt4*tt8-1.0E+0*F(1,3)*tt10
tt28 = 1.0E+0*tt12*tt4
tt29 = 1.0E+0*tt4*tt9-1.0E+0*F(2,2)*tt10
tt30 = 1.0E+0*F(1,2)*tt10+1.0E+0*tt4*tt15
tt31 = 1.0E+0*tt17*tt4
tt32 = 1.0E+0*tt8*tt6
tt33 = 1.0E+0*tt12*tt6
tt34 = 1.0E+0*tt9*tt6
tt35 = 1.0E+0*F(3,1)*tt10+1.0E+0*tt15*tt6
tt36 = 1.0E+0*tt17*tt6-1.0E+0*F(2,1)*tt10
tt37 = 1.0E+0*tt12*tt8
tt38 = 1.0E+0*tt9*tt8-1.0E+0*F(3,1)*tt10
tt39 = 1.0E+0*tt15*tt8
tt40 = 1.0E+0*F(1,1)*tt10+1.0E+0*tt17*tt8
tt41 = 1.0E+0*F(2,1)*tt10+1.0E+0*tt12*tt9
tt42 = 1.0E+0*tt12*tt15-1.0E+0*F(1,1)*tt10
tt43 = 1.0E+0*tt17*tt12
tt44 = 1.0E+0*tt15*tt9
tt45 = 1.0E+0*tt17*tt9
tt46 = 1.0E+0*tt17*tt15
hes(1,1) = 1.0E+0*tt1**2
hes(1,2) = tt3
hes(1,3) = tt5
hes(1,4) = tt7
hes(1,5) = tt11
hes(1,6) = tt13
hes(1,7) = tt14
hes(1,8) = tt16
hes(1,9) = tt18
hes(2,1) = tt3
hes(2,2) = 1.0E+0*tt2**2
hes(2,3) = tt19
hes(2,4) = tt20
hes(2,5) = tt21
hes(2,6) = tt22
hes(2,7) = tt23
hes(2,8) = tt24
hes(2,9) = tt25
hes(3,1) = tt5
hes(3,2) = tt19
hes(3,3) = 1.0E+0*tt4**2
hes(3,4) = tt26
hes(3,5) = tt27
hes(3,6) = tt28
hes(3,7) = tt29
hes(3,8) = tt30
hes(3,9) = tt31
hes(4,1) = tt7
hes(4,2) = tt20
hes(4,3) = tt26
hes(4,4) = 1.0E+0*tt6**2
hes(4,5) = tt32
hes(4,6) = tt33
hes(4,7) = tt34
hes(4,8) = tt35
hes(4,9) = tt36
hes(5,1) = tt11
hes(5,2) = tt21
hes(5,3) = tt27
hes(5,4) = tt32
hes(5,5) = 1.0E+0*tt8**2
hes(5,6) = tt37
hes(5,7) = tt38
hes(5,8) = tt39
hes(5,9) = tt40
hes(6,1) = tt13
hes(6,2) = tt22
hes(6,3) = tt28
hes(6,4) = tt33
hes(6,5) = tt37
hes(6,6) = 1.0E+0*tt12**2
hes(6,7) = tt41
hes(6,8) = tt42
hes(6,9) = tt43
hes(7,1) = tt14
hes(7,2) = tt23
hes(7,3) = tt29
hes(7,4) = tt34
hes(7,5) = tt38
hes(7,6) = tt41
hes(7,7) = 1.0E+0*tt9**2
hes(7,8) = tt44
hes(7,9) = tt45
hes(8,1) = tt16
hes(8,2) = tt24
hes(8,3) = tt30
hes(8,4) = tt35
hes(8,5) = tt39
hes(8,6) = tt42
hes(8,7) = tt44
hes(8,8) = 1.0E+0*tt15**2
hes(8,9) = tt46
hes(9,1) = tt18
hes(9,2) = tt25
hes(9,3) = tt31
hes(9,4) = tt36
hes(9,5) = tt40
hes(9,6) = tt43
hes(9,7) = tt45
hes(9,8) = tt46
hes(9,9) = 1.0E+0*tt17**2
END
SUBROUTINE &
&pixar18_neohookean_mu_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
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
tt1 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt2 = F(2,1)*F(3,3)-F(2,3)*F(3,1)
tt3 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt4 = F(1,1)**2
tt5 = F(1,2)**2
tt6 = F(1,3)**2
tt7 = F(2,1)**2
tt8 = F(2,2)**2
tt9 = F(2,3)**2
tt10 = F(3,1)**2
tt11 = F(3,2)**2
tt12 = F(3,3)**2
val(1,1) = (2.0E+0*((-log(tt12+tt11+tt10+tt9+tt8+tt7+tt6+tt5+tt4+&
&1))+tt12+tt11+tt10+tt9+tt8+tt7+tt6+tt5+tt4))/3.0E+0+4.16666666666&
&6667E-1*(F(1,1)*tt3-F(1,2)*tt2+F(1,3)*tt1-1)**2-F(1,1)*tt3+F(1,2)&
&*tt2-F(1,3)*tt1
END
SUBROUTINE &
&pixar18_neohookean_mu_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt3 = -F(2,3)*F(3,1)
tt4 = F(2,1)*F(3,3)
tt5 = F(1,1)*tt1-F(1,2)*(tt4+tt3)+F(1,3)*tt2-1
tt6 = 1/(F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,1)&
&**2+F(1,3)**2+F(1,2)**2+F(1,1)**2+1)
jac(1,1) = (2.0E+0*(2*F(1,1)-2*F(1,1)*tt6))/3.0E+0+8.333333333333&
&334E-1*tt1*tt5-F(2,2)*F(3,3)+F(2,3)*F(3,2)
jac(1,2) = (2.0E+0*(2*F(2,1)-2*F(2,1)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(1,3)*F(3,2)-F(1,2)*F(3,3))*tt5+F(1,2)*F(3,3)-F(1,3)*F(3&
&,2)
jac(1,3) = (2.0E+0*(2*F(3,1)-2*F(3,1)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(1,2)*F(2,3)-F(1,3)*F(2,2))*tt5-F(1,2)*F(2,3)+F(1,3)*F(2&
&,2)
jac(1,4) = (2.0E+0*(2*F(1,2)-2*F(1,2)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(2,3)*F(3,1)-F(2,1)*F(3,3))*tt5+tt4+tt3
jac(1,5) = (2.0E+0*(2*F(2,2)-2*F(2,2)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(1,1)*F(3,3)-F(1,3)*F(3,1))*tt5-F(1,1)*F(3,3)+F(1,3)*F(3&
&,1)
jac(1,6) = (2.0E+0*(2*F(3,2)-2*F(3,2)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt5+F(1,1)*F(2,3)-F(1,3)*F(2&
&,1)
jac(1,7) = (2.0E+0*(2*F(1,3)-2*F(1,3)*tt6))/3.0E+0+8.333333333333&
&334E-1*tt2*tt5-F(2,1)*F(3,2)+F(2,2)*F(3,1)
jac(1,8) = (2.0E+0*(2*F(2,3)-2*F(2,3)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(1,2)*F(3,1)-F(1,1)*F(3,2))*tt5+F(1,1)*F(3,2)-F(1,2)*F(3&
&,1)
jac(1,9) = (2.0E+0*(2*F(3,3)-2*F(3,3)*tt6))/3.0E+0+8.333333333333&
&334E-1*(F(1,1)*F(2,2)-F(1,2)*F(2,1))*tt5-F(1,1)*F(2,2)+F(1,2)*F(2&
&,1)
END
SUBROUTINE &
&pixar18_neohookean_mu_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
tt1 = F(2,2)*F(3,3)-F(2,3)*F(3,2)
tt2 = F(1,1)**2
tt3 = F(1,2)**2
tt4 = F(1,3)**2
tt5 = F(2,1)**2
tt6 = F(2,2)**2
tt7 = F(2,3)**2
tt8 = F(3,1)**2
tt9 = F(3,2)**2
tt10 = F(3,3)**2
tt11 = tt10+tt9+tt8+tt7+tt6+tt5+tt4+tt3+tt2+1
tt12 = 1/tt11**2
tt13 = -2/tt11
tt14 = F(1,3)*F(3,2)-F(1,2)*F(3,3)
tt15 = (8.0E+0*F(1,1)*F(2,1)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&14*tt1
tt16 = F(1,2)*F(2,3)-F(1,3)*F(2,2)
tt17 = (8.0E+0*F(1,1)*F(3,1)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&16*tt1
tt18 = F(2,3)*F(3,1)-F(2,1)*F(3,3)
tt19 = (8.0E+0*F(1,1)*F(1,2)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&18*tt1
tt20 = F(1,1)*F(3,3)-F(1,3)*F(3,1)
tt21 = F(2,1)*F(3,2)-F(2,2)*F(3,1)
tt22 = F(1,1)*tt1-F(1,2)*(F(2,1)*F(3,3)-F(2,3)*F(3,1))+F(1,3)*tt2&
&1-1
tt23 = (8.0E+0*F(1,1)*F(2,2)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&3,3)*tt22+8.333333333333334E-1*tt20*tt1-F(3,3)
tt24 = F(1,3)*F(2,1)-F(1,1)*F(2,3)
tt25 = (8.0E+0*F(1,1)*F(3,2)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&2,3)*tt22+8.333333333333334E-1*tt24*tt1+F(2,3)
tt26 = (8.0E+0*F(1,1)*F(1,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&21*tt1
tt27 = F(1,2)*F(3,1)-F(1,1)*F(3,2)
tt28 = (8.0E+0*F(1,1)*F(2,3)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&3,2)*tt22+8.333333333333334E-1*tt27*tt1+F(3,2)
tt29 = F(1,1)*F(2,2)-F(1,2)*F(2,1)
tt30 = (8.0E+0*F(1,1)*F(3,3)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&2,2)*tt22+8.333333333333334E-1*tt29*tt1-F(2,2)
tt31 = (8.0E+0*F(2,1)*F(3,1)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&16*tt14
tt32 = (8.0E+0*F(1,2)*F(2,1)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&3,3)*tt22+8.333333333333334E-1*tt14*tt18+F(3,3)
tt33 = (8.0E+0*F(2,1)*F(2,2)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&20*tt14
tt34 = (8.0E+0*F(2,1)*F(3,2)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&1,3)*tt22+8.333333333333334E-1*tt24*tt14-F(1,3)
tt35 = (8.0E+0*F(1,3)*F(2,1)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&3,2)*tt22+8.333333333333334E-1*tt21*tt14-F(3,2)
tt36 = (8.0E+0*F(2,1)*F(2,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&27*tt14
tt37 = (8.0E+0*F(2,1)*F(3,3)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&1,2)*tt22+8.333333333333334E-1*tt29*tt14+F(1,2)
tt38 = (8.0E+0*F(1,2)*F(3,1)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&2,3)*tt22+8.333333333333334E-1*tt16*tt18-F(2,3)
tt39 = (8.0E+0*F(2,2)*F(3,1)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&1,3)*tt22+8.333333333333334E-1*tt16*tt20+F(1,3)
tt40 = (8.0E+0*F(3,1)*F(3,2)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&24*tt16
tt41 = (8.0E+0*F(1,3)*F(3,1)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&2,2)*tt22+8.333333333333334E-1*tt16*tt21+F(2,2)
tt42 = (8.0E+0*F(2,3)*F(3,1)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&1,2)*tt22+8.333333333333334E-1*tt16*tt27-F(1,2)
tt43 = (8.0E+0*F(3,1)*F(3,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&29*tt16
tt44 = (8.0E+0*F(1,2)*F(2,2)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&20*tt18
tt45 = (8.0E+0*F(1,2)*F(3,2)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&24*tt18
tt46 = (8.0E+0*F(1,2)*F(1,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&21*tt18
tt47 = (8.0E+0*F(1,2)*F(2,3)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&3,1)*tt22+8.333333333333334E-1*tt27*tt18-F(3,1)
tt48 = (8.0E+0*F(1,2)*F(3,3)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&2,1)*tt22+8.333333333333334E-1*tt29*tt18+F(2,1)
tt49 = (8.0E+0*F(2,2)*F(3,2)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&24*tt20
tt50 = (8.0E+0*F(1,3)*F(2,2)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&3,1)*tt22+8.333333333333334E-1*tt21*tt20+F(3,1)
tt51 = (8.0E+0*F(2,2)*F(2,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&27*tt20
tt52 = (8.0E+0*F(2,2)*F(3,3)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&1,1)*tt22+8.333333333333334E-1*tt29*tt20-F(1,1)
tt53 = (8.0E+0*F(1,3)*F(3,2)*tt12)/3.0E+0+8.333333333333334E-1*F(&
&2,1)*tt22+8.333333333333334E-1*tt24*tt21-F(2,1)
tt54 = (8.0E+0*F(2,3)*F(3,2)*tt12)/3.0E+0-8.333333333333334E-1*F(&
&1,1)*tt22+8.333333333333334E-1*tt24*tt27+F(1,1)
tt55 = (8.0E+0*F(3,2)*F(3,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&29*tt24
tt56 = (8.0E+0*F(1,3)*F(2,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&27*tt21
tt57 = (8.0E+0*F(1,3)*F(3,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&29*tt21
tt58 = (8.0E+0*F(2,3)*F(3,3)*tt12)/3.0E+0+8.333333333333334E-1*tt&
&29*tt27
hes(1,1) = (2.0E+0*(tt13+4*tt2*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt1**2
hes(1,2) = tt15
hes(1,3) = tt17
hes(1,4) = tt19
hes(1,5) = tt23
hes(1,6) = tt25
hes(1,7) = tt26
hes(1,8) = tt28
hes(1,9) = tt30
hes(2,1) = tt15
hes(2,2) = (2.0E+0*(tt13+4*tt5*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt14**2
hes(2,3) = tt31
hes(2,4) = tt32
hes(2,5) = tt33
hes(2,6) = tt34
hes(2,7) = tt35
hes(2,8) = tt36
hes(2,9) = tt37
hes(3,1) = tt17
hes(3,2) = tt31
hes(3,3) = (2.0E+0*(tt13+4*tt8*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt16**2
hes(3,4) = tt38
hes(3,5) = tt39
hes(3,6) = tt40
hes(3,7) = tt41
hes(3,8) = tt42
hes(3,9) = tt43
hes(4,1) = tt19
hes(4,2) = tt32
hes(4,3) = tt38
hes(4,4) = (2.0E+0*(tt13+4*tt3*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt18**2
hes(4,5) = tt44
hes(4,6) = tt45
hes(4,7) = tt46
hes(4,8) = tt47
hes(4,9) = tt48
hes(5,1) = tt23
hes(5,2) = tt33
hes(5,3) = tt39
hes(5,4) = tt44
hes(5,5) = (2.0E+0*(tt13+4*tt6*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt20**2
hes(5,6) = tt49
hes(5,7) = tt50
hes(5,8) = tt51
hes(5,9) = tt52
hes(6,1) = tt25
hes(6,2) = tt34
hes(6,3) = tt40
hes(6,4) = tt45
hes(6,5) = tt49
hes(6,6) = (2.0E+0*(tt13+4*tt9*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt24**2
hes(6,7) = tt53
hes(6,8) = tt54
hes(6,9) = tt55
hes(7,1) = tt26
hes(7,2) = tt35
hes(7,3) = tt41
hes(7,4) = tt46
hes(7,5) = tt50
hes(7,6) = tt53
hes(7,7) = (2.0E+0*(tt13+4*tt4*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt21**2
hes(7,8) = tt56
hes(7,9) = tt57
hes(8,1) = tt28
hes(8,2) = tt36
hes(8,3) = tt42
hes(8,4) = tt47
hes(8,5) = tt51
hes(8,6) = tt54
hes(8,7) = tt56
hes(8,8) = (2.0E+0*(tt13+4*tt7*tt12+2))/3.0E+0+8.333333333333334E&
&-1*tt27**2
hes(8,9) = tt58
hes(9,1) = tt30
hes(9,2) = tt37
hes(9,3) = tt43
hes(9,4) = tt48
hes(9,5) = tt52
hes(9,6) = tt55
hes(9,7) = tt57
hes(9,8) = tt58
hes(9,9) = (2.0E+0*(tt13+4*tt10*tt12+2))/3.0E+0+8.333333333333334&
&E-1*tt29**2
END
SUBROUTINE &
&small_general_linear_elas_3d_val(&
&  val &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = 1.0E+0*F(1,1)-1
tt2 = F(2,1)+F(1,2)
tt3 = 1.0E+0*F(2,2)-1
tt4 = F(3,1)+F(1,3)
tt5 = F(3,2)+F(2,3)
tt6 = 1.0E+0*F(3,3)-1
val(1,1) = 5.0E-1*(1.0E+0*tt2*(1.0E+0*tt2*C(6,6)+1.0E+0*tt4*C(6,5&
&)+1.0E+0*tt5*C(6,4)+tt6*C(6,3)+tt3*C(6,2)+tt1*C(6,1))+1.0E+0*tt4*&
&(1.0E+0*tt2*C(5,6)+1.0E+0*tt4*C(5,5)+1.0E+0*tt5*C(5,4)+tt6*C(5,3)&
&+tt3*C(5,2)+tt1*C(5,1))+1.0E+0*tt5*(1.0E+0*tt2*C(4,6)+1.0E+0*tt4*&
&C(4,5)+1.0E+0*tt5*C(4,4)+tt6*C(4,3)+tt3*C(4,2)+tt1*C(4,1))+tt6*(1&
&.0E+0*tt2*C(3,6)+1.0E+0*tt4*C(3,5)+1.0E+0*tt5*C(3,4)+C(3,3)*tt6+t&
&t3*C(3,2)+tt1*C(3,1))+tt3*(C(2,3)*tt6+1.0E+0*C(2,4)*tt5+1.0E+0*C(&
&2,5)*tt4+1.0E+0*tt2*C(2,6)+C(2,2)*tt3+tt1*C(2,1))+tt1*(C(1,3)*tt6&
&+1.0E+0*C(1,4)*tt5+1.0E+0*C(1,5)*tt4+C(1,2)*tt3+1.0E+0*C(1,6)*tt2&
&+C(1,1)*tt1))
END
SUBROUTINE &
&small_general_linear_elas_3d_jac(&
&  jac &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
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
tt1 = 1.0E+0*F(1,1)-1
tt2 = 1.0E+0*F(2,2)-1
tt3 = 1.0E+0*F(3,3)-1
tt4 = F(2,1)+F(1,2)
tt5 = F(3,1)+F(1,3)
tt6 = F(3,2)+F(2,3)
tt7 = 1.0E+0*tt4*C(6,6)
tt8 = 5.0E-1*(1.0E+0*(tt7+1.0E+0*tt5*C(6,5)+1.0E+0*tt6*C(6,4)+tt3&
&*C(6,3)+tt2*C(6,2)+tt1*C(6,1))+tt7+1.0E+0*tt5*C(5,6)+1.0E+0*tt6*C&
&(4,6)+1.0E+0*tt3*C(3,6)+1.0E+0*tt2*C(2,6)+1.0E+0*tt1*C(1,6))
tt9 = 1.0E+0*tt5*C(5,5)
tt10 = 5.0E-1*(1.0E+0*tt4*C(6,5)+1.0E+0*(1.0E+0*tt4*C(5,6)+tt9+1.&
&0E+0*tt6*C(5,4)+tt3*C(5,3)+tt2*C(5,2)+tt1*C(5,1))+tt9+1.0E+0*tt6*&
&C(4,5)+1.0E+0*tt3*C(3,5)+1.0E+0*tt2*C(2,5)+1.0E+0*tt1*C(1,5))
tt11 = 1.0E+0*tt6*C(4,4)
tt12 = 5.0E-1*(1.0E+0*tt4*C(6,4)+1.0E+0*tt5*C(5,4)+1.0E+0*(1.0E+0&
&*tt4*C(4,6)+1.0E+0*tt5*C(4,5)+tt11+tt3*C(4,3)+tt2*C(4,2)+tt1*C(4,&
&1))+tt11+1.0E+0*tt3*C(3,4)+1.0E+0*tt2*C(2,4)+1.0E+0*tt1*C(1,4))
jac(1,1) = 5.0E-1*(1.0E+0*tt4*C(6,1)+1.0E+0*tt5*C(5,1)+1.0E+0*tt6&
&*C(4,1)+1.0E+0*(C(1,3)*tt3+1.0E+0*C(1,4)*tt6+1.0E+0*C(1,5)*tt5+C(&
&1,2)*tt2+1.0E+0*C(1,6)*tt4+C(1,1)*tt1)+1.0E+0*C(3,1)*tt3+1.0E+0*C&
&(2,1)*tt2+1.0E+0*C(1,1)*tt1)
jac(1,2) = tt8
jac(1,3) = tt10
jac(1,4) = tt8
jac(1,5) = 5.0E-1*(1.0E+0*tt4*C(6,2)+1.0E+0*tt5*C(5,2)+1.0E+0*tt6&
&*C(4,2)+1.0E+0*(C(2,3)*tt3+1.0E+0*C(2,4)*tt6+1.0E+0*C(2,5)*tt5+1.&
&0E+0*tt4*C(2,6)+C(2,2)*tt2+tt1*C(2,1))+1.0E+0*C(3,2)*tt3+1.0E+0*C&
&(2,2)*tt2+1.0E+0*tt1*C(1,2))
jac(1,6) = tt12
jac(1,7) = tt10
jac(1,8) = tt12
jac(1,9) = 5.0E-1*(1.0E+0*tt4*C(6,3)+1.0E+0*tt5*C(5,3)+1.0E+0*tt6&
&*C(4,3)+1.0E+0*(1.0E+0*tt4*C(3,6)+1.0E+0*tt5*C(3,5)+1.0E+0*tt6*C(&
&3,4)+C(3,3)*tt3+tt2*C(3,2)+tt1*C(3,1))+1.0E+0*C(3,3)*tt3+1.0E+0*t&
&t2*C(2,3)+1.0E+0*tt1*C(1,3))
END
SUBROUTINE &
&small_general_linear_elas_3d_hes(&
&  hes &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
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
tt1 = 5.0E-1*(1.0E+0*C(6,1)+1.0E+0*C(1,6))
tt2 = 5.0E-1*(1.0E+0*C(5,1)+1.0E+0*C(1,5))
tt3 = 5.0E-1*(1.0E+0*C(2,1)+1.0E+0*C(1,2))
tt4 = 5.0E-1*(1.0E+0*C(4,1)+1.0E+0*C(1,4))
tt5 = 5.0E-1*(1.0E+0*C(3,1)+1.0E+0*C(1,3))
tt6 = 1.0E+0*C(6,6)
tt7 = 5.0E-1*(1.0E+0*C(6,5)+1.0E+0*C(5,6))
tt8 = 5.0E-1*(1.0E+0*C(6,2)+1.0E+0*C(2,6))
tt9 = 5.0E-1*(1.0E+0*C(6,4)+1.0E+0*C(4,6))
tt10 = 5.0E-1*(1.0E+0*C(6,3)+1.0E+0*C(3,6))
tt12 = 1.0E+0*C(5,5)
tt13 = 5.0E-1*(1.0E+0*C(5,2)+1.0E+0*C(2,5))
tt14 = 5.0E-1*(1.0E+0*C(5,4)+1.0E+0*C(4,5))
tt15 = 5.0E-1*(1.0E+0*C(5,3)+1.0E+0*C(3,5))
tt17 = 5.0E-1*(1.0E+0*C(4,2)+1.0E+0*C(2,4))
tt18 = 5.0E-1*(1.0E+0*C(3,2)+1.0E+0*C(2,3))
tt19 = 1.0E+0*C(4,4)
tt20 = 5.0E-1*(1.0E+0*C(4,3)+1.0E+0*C(3,4))
hes(1,1) = 1.0E+0*C(1,1)
hes(1,2) = tt1
hes(1,3) = tt2
hes(1,4) = tt1
hes(1,5) = tt3
hes(1,6) = tt4
hes(1,7) = tt2
hes(1,8) = tt4
hes(1,9) = tt5
hes(2,1) = tt1
hes(2,2) = tt6
hes(2,3) = tt7
hes(2,4) = tt6
hes(2,5) = tt8
hes(2,6) = tt9
hes(2,7) = tt7
hes(2,8) = tt9
hes(2,9) = tt10
hes(3,1) = tt2
hes(3,2) = tt7
hes(3,3) = tt12
hes(3,4) = tt7
hes(3,5) = tt13
hes(3,6) = tt14
hes(3,7) = tt12
hes(3,8) = tt14
hes(3,9) = tt15
hes(4,1) = tt1
hes(4,2) = tt6
hes(4,3) = tt7
hes(4,4) = tt6
hes(4,5) = tt8
hes(4,6) = tt9
hes(4,7) = tt7
hes(4,8) = tt9
hes(4,9) = tt10
hes(5,1) = tt3
hes(5,2) = tt8
hes(5,3) = tt13
hes(5,4) = tt8
hes(5,5) = 1.0E+0*C(2,2)
hes(5,6) = tt17
hes(5,7) = tt13
hes(5,8) = tt17
hes(5,9) = tt18
hes(6,1) = tt4
hes(6,2) = tt9
hes(6,3) = tt14
hes(6,4) = tt9
hes(6,5) = tt17
hes(6,6) = tt19
hes(6,7) = tt14
hes(6,8) = tt19
hes(6,9) = tt20
hes(7,1) = tt2
hes(7,2) = tt7
hes(7,3) = tt12
hes(7,4) = tt7
hes(7,5) = tt13
hes(7,6) = tt14
hes(7,7) = tt12
hes(7,8) = tt14
hes(7,9) = tt15
hes(8,1) = tt4
hes(8,2) = tt9
hes(8,3) = tt14
hes(8,4) = tt9
hes(8,5) = tt17
hes(8,6) = tt19
hes(8,7) = tt14
hes(8,8) = tt19
hes(8,9) = tt20
hes(9,1) = tt5
hes(9,2) = tt10
hes(9,3) = tt15
hes(9,4) = tt10
hes(9,5) = tt18
hes(9,6) = tt20
hes(9,7) = tt15
hes(9,8) = tt20
hes(9,9) = 1.0E+0*C(3,3)
END
SUBROUTINE &
&green_general_linear_elas_3d_val(&
&  val &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = F(3,1)**2+F(2,1)**2+F(1,1)**2-1
tt2 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(3,2)**2+F(2,2)**2+F(1,2)**2-1
tt4 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt5 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt6 = F(3,3)**2+F(2,3)**2+F(1,3)**2-1
val(1,1) = 5.0E-1*(1.0E+0*tt2*(1.0E+0*tt2*C(6,6)+1.0E+0*tt4*C(6,5&
&)+1.0E+0*tt5*C(6,4)+5.0E-1*tt6*C(6,3)+5.0E-1*tt3*C(6,2)+5.0E-1*tt&
&1*C(6,1))+1.0E+0*tt4*(1.0E+0*tt2*C(5,6)+1.0E+0*tt4*C(5,5)+1.0E+0*&
&tt5*C(5,4)+5.0E-1*tt6*C(5,3)+5.0E-1*tt3*C(5,2)+5.0E-1*tt1*C(5,1))&
&+1.0E+0*tt5*(1.0E+0*tt2*C(4,6)+1.0E+0*tt4*C(4,5)+1.0E+0*tt5*C(4,4&
&)+5.0E-1*tt6*C(4,3)+5.0E-1*tt3*C(4,2)+5.0E-1*tt1*C(4,1))+5.0E-1*t&
&t6*(1.0E+0*tt2*C(3,6)+1.0E+0*tt4*C(3,5)+1.0E+0*tt5*C(3,4)+5.0E-1*&
&C(3,3)*tt6+5.0E-1*C(3,2)*tt3+5.0E-1*C(3,1)*tt1)+5.0E-1*tt3*(5.0E-&
&1*C(2,3)*tt6+1.0E+0*C(2,4)*tt5+1.0E+0*C(2,5)*tt4+5.0E-1*C(2,2)*tt&
&3+1.0E+0*C(2,6)*tt2+5.0E-1*C(2,1)*tt1)+5.0E-1*tt1*(5.0E-1*C(1,3)*&
&tt6+1.0E+0*C(1,4)*tt5+1.0E+0*C(1,5)*tt4+5.0E-1*C(1,2)*tt3+1.0E+0*&
&C(1,6)*tt2+5.0E-1*C(1,1)*tt1))
END
SUBROUTINE &
&green_general_linear_elas_3d_jac(&
&  jac &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
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
tt1 = F(3,1)**2+F(2,1)**2+F(1,1)**2-1
tt2 = F(3,2)**2+F(2,2)**2+F(1,2)**2-1
tt3 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt4 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt5 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt6 = F(3,3)**2+F(2,3)**2+F(1,3)**2-1
tt7 = 5.0E-1*C(1,3)*tt6+1.0E+0*C(1,4)*tt5+1.0E+0*C(1,5)*tt4+5.0E-&
&1*C(1,2)*tt2+1.0E+0*C(1,6)*tt3+5.0E-1*C(1,1)*tt1
tt8 = 1.0E+0*tt3*C(5,6)+1.0E+0*tt4*C(5,5)+1.0E+0*tt5*C(5,4)+5.0E-&
&1*tt6*C(5,3)+5.0E-1*tt2*C(5,2)+5.0E-1*tt1*C(5,1)
tt9 = 1.0E+0*tt3*C(6,6)+1.0E+0*tt4*C(6,5)+1.0E+0*tt5*C(6,4)+5.0E-&
&1*tt6*C(6,3)+5.0E-1*tt2*C(6,2)+5.0E-1*tt1*C(6,1)
tt10 = 5.0E-1*C(2,3)*tt6+1.0E+0*C(2,4)*tt5+1.0E+0*C(2,5)*tt4+5.0E&
&-1*C(2,2)*tt2+1.0E+0*C(2,6)*tt3+5.0E-1*C(2,1)*tt1
tt11 = 1.0E+0*tt3*C(4,6)+1.0E+0*tt4*C(4,5)+1.0E+0*tt5*C(4,4)+5.0E&
&-1*tt6*C(4,3)+5.0E-1*tt2*C(4,2)+5.0E-1*tt1*C(4,1)
tt12 = 1.0E+0*tt3*C(3,6)+1.0E+0*tt4*C(3,5)+1.0E+0*tt5*C(3,4)+5.0E&
&-1*C(3,3)*tt6+5.0E-1*C(3,2)*tt2+5.0E-1*C(3,1)*tt1
jac(1,1) = 5.0E-1*(1.0E+0*F(1,2)*tt9+1.0E+0*tt3*(1.0E+0*F(1,2)*C(&
&6,6)+1.0E+0*F(1,3)*C(6,5)+1.0E+0*F(1,1)*C(6,1))+1.0E+0*F(1,3)*tt8&
&+1.0E+0*tt4*(1.0E+0*F(1,2)*C(5,6)+1.0E+0*F(1,3)*C(5,5)+1.0E+0*F(1&
&,1)*C(5,1))+1.0E+0*tt5*(1.0E+0*F(1,2)*C(4,6)+1.0E+0*F(1,3)*C(4,5)&
&+1.0E+0*F(1,1)*C(4,1))+5.0E-1*tt6*(1.0E+0*F(1,2)*C(3,6)+1.0E+0*F(&
&1,3)*C(3,5)+1.0E+0*F(1,1)*C(3,1))+1.0E+0*F(1,1)*tt7+5.0E-1*(1.0E+&
&0*F(1,2)*C(2,6)+1.0E+0*F(1,3)*C(2,5)+1.0E+0*F(1,1)*C(2,1))*tt2+5.&
&0E-1*(1.0E+0*F(1,2)*C(1,6)+1.0E+0*F(1,3)*C(1,5)+1.0E+0*C(1,1)*F(1&
&,1))*tt1)
jac(1,2) = 5.0E-1*(1.0E+0*F(2,2)*tt9+1.0E+0*tt3*(1.0E+0*F(2,2)*C(&
&6,6)+1.0E+0*F(2,3)*C(6,5)+1.0E+0*F(2,1)*C(6,1))+1.0E+0*F(2,3)*tt8&
&+1.0E+0*tt4*(1.0E+0*F(2,2)*C(5,6)+1.0E+0*F(2,3)*C(5,5)+1.0E+0*F(2&
&,1)*C(5,1))+1.0E+0*tt5*(1.0E+0*F(2,2)*C(4,6)+1.0E+0*F(2,3)*C(4,5)&
&+1.0E+0*F(2,1)*C(4,1))+5.0E-1*tt6*(1.0E+0*F(2,2)*C(3,6)+1.0E+0*F(&
&2,3)*C(3,5)+1.0E+0*F(2,1)*C(3,1))+1.0E+0*F(2,1)*tt7+5.0E-1*(1.0E+&
&0*F(2,2)*C(2,6)+1.0E+0*F(2,3)*C(2,5)+1.0E+0*C(2,1)*F(2,1))*tt2+5.&
&0E-1*(1.0E+0*C(1,5)*F(2,3)+1.0E+0*C(1,6)*F(2,2)+1.0E+0*C(1,1)*F(2&
&,1))*tt1)
jac(1,3) = 5.0E-1*(1.0E+0*F(3,2)*tt9+1.0E+0*tt3*(1.0E+0*F(3,2)*C(&
&6,6)+1.0E+0*F(3,3)*C(6,5)+1.0E+0*F(3,1)*C(6,1))+1.0E+0*F(3,3)*tt8&
&+1.0E+0*tt4*(1.0E+0*F(3,2)*C(5,6)+1.0E+0*F(3,3)*C(5,5)+1.0E+0*F(3&
&,1)*C(5,1))+1.0E+0*tt5*(1.0E+0*F(3,2)*C(4,6)+1.0E+0*F(3,3)*C(4,5)&
&+1.0E+0*F(3,1)*C(4,1))+5.0E-1*tt6*(1.0E+0*F(3,2)*C(3,6)+1.0E+0*F(&
&3,3)*C(3,5)+1.0E+0*C(3,1)*F(3,1))+1.0E+0*F(3,1)*tt7+5.0E-1*tt2*(1&
&.0E+0*C(2,5)*F(3,3)+1.0E+0*C(2,6)*F(3,2)+1.0E+0*C(2,1)*F(3,1))+5.&
&0E-1*tt1*(1.0E+0*C(1,5)*F(3,3)+1.0E+0*C(1,6)*F(3,2)+1.0E+0*C(1,1)&
&*F(3,1)))
jac(1,4) = 5.0E-1*(1.0E+0*F(1,1)*tt9+1.0E+0*tt3*(1.0E+0*F(1,1)*C(&
&6,6)+1.0E+0*F(1,3)*C(6,4)+1.0E+0*F(1,2)*C(6,2))+1.0E+0*tt4*(1.0E+&
&0*F(1,1)*C(5,6)+1.0E+0*F(1,3)*C(5,4)+1.0E+0*F(1,2)*C(5,2))+1.0E+0&
&*F(1,3)*tt11+1.0E+0*tt5*(1.0E+0*F(1,1)*C(4,6)+1.0E+0*F(1,3)*C(4,4&
&)+1.0E+0*F(1,2)*C(4,2))+5.0E-1*tt6*(1.0E+0*F(1,1)*C(3,6)+1.0E+0*F&
&(1,3)*C(3,4)+1.0E+0*F(1,2)*C(3,2))+1.0E+0*F(1,2)*tt10+5.0E-1*(1.0&
&E+0*F(1,1)*C(2,6)+1.0E+0*F(1,3)*C(2,4)+1.0E+0*F(1,2)*C(2,2))*tt2+&
&5.0E-1*(1.0E+0*F(1,1)*C(1,6)+1.0E+0*F(1,3)*C(1,4)+1.0E+0*C(1,2)*F&
&(1,2))*tt1)
jac(1,5) = 5.0E-1*(1.0E+0*F(2,1)*tt9+1.0E+0*tt3*(1.0E+0*F(2,1)*C(&
&6,6)+1.0E+0*F(2,3)*C(6,4)+1.0E+0*F(2,2)*C(6,2))+1.0E+0*tt4*(1.0E+&
&0*F(2,1)*C(5,6)+1.0E+0*F(2,3)*C(5,4)+1.0E+0*F(2,2)*C(5,2))+1.0E+0&
&*F(2,3)*tt11+1.0E+0*tt5*(1.0E+0*F(2,1)*C(4,6)+1.0E+0*F(2,3)*C(4,4&
&)+1.0E+0*F(2,2)*C(4,2))+5.0E-1*tt6*(1.0E+0*F(2,1)*C(3,6)+1.0E+0*F&
&(2,3)*C(3,4)+1.0E+0*F(2,2)*C(3,2))+1.0E+0*F(2,2)*tt10+5.0E-1*(1.0&
&E+0*F(2,1)*C(2,6)+1.0E+0*F(2,3)*C(2,4)+1.0E+0*C(2,2)*F(2,2))*tt2+&
&5.0E-1*(1.0E+0*C(1,4)*F(2,3)+1.0E+0*C(1,2)*F(2,2)+1.0E+0*C(1,6)*F&
&(2,1))*tt1)
jac(1,6) = 5.0E-1*(1.0E+0*F(3,1)*tt9+1.0E+0*tt3*(1.0E+0*F(3,1)*C(&
&6,6)+1.0E+0*F(3,3)*C(6,4)+1.0E+0*F(3,2)*C(6,2))+1.0E+0*tt4*(1.0E+&
&0*F(3,1)*C(5,6)+1.0E+0*F(3,3)*C(5,4)+1.0E+0*F(3,2)*C(5,2))+1.0E+0&
&*F(3,3)*tt11+1.0E+0*tt5*(1.0E+0*F(3,1)*C(4,6)+1.0E+0*F(3,3)*C(4,4&
&)+1.0E+0*F(3,2)*C(4,2))+5.0E-1*tt6*(1.0E+0*F(3,1)*C(3,6)+1.0E+0*F&
&(3,3)*C(3,4)+1.0E+0*C(3,2)*F(3,2))+1.0E+0*F(3,2)*tt10+5.0E-1*tt2*&
&(1.0E+0*C(2,4)*F(3,3)+1.0E+0*C(2,2)*F(3,2)+1.0E+0*C(2,6)*F(3,1))+&
&5.0E-1*tt1*(1.0E+0*C(1,4)*F(3,3)+1.0E+0*C(1,2)*F(3,2)+1.0E+0*C(1,&
&6)*F(3,1)))
jac(1,7) = 5.0E-1*(1.0E+0*tt3*(1.0E+0*F(1,1)*C(6,5)+1.0E+0*F(1,2)&
&*C(6,4)+1.0E+0*F(1,3)*C(6,3))+1.0E+0*F(1,1)*tt8+1.0E+0*tt4*(1.0E+&
&0*F(1,1)*C(5,5)+1.0E+0*F(1,2)*C(5,4)+1.0E+0*F(1,3)*C(5,3))+1.0E+0&
&*F(1,2)*tt11+1.0E+0*tt5*(1.0E+0*F(1,1)*C(4,5)+1.0E+0*F(1,2)*C(4,4&
&)+1.0E+0*F(1,3)*C(4,3))+1.0E+0*F(1,3)*tt12+5.0E-1*tt6*(1.0E+0*F(1&
&,1)*C(3,5)+1.0E+0*F(1,2)*C(3,4)+1.0E+0*F(1,3)*C(3,3))+5.0E-1*(1.0&
&E+0*F(1,1)*C(2,5)+1.0E+0*F(1,2)*C(2,4)+1.0E+0*F(1,3)*C(2,3))*tt2+&
&5.0E-1*(1.0E+0*F(1,1)*C(1,5)+1.0E+0*F(1,2)*C(1,4)+1.0E+0*C(1,3)*F&
&(1,3))*tt1)
jac(1,8) = 5.0E-1*(1.0E+0*tt3*(1.0E+0*F(2,1)*C(6,5)+1.0E+0*F(2,2)&
&*C(6,4)+1.0E+0*F(2,3)*C(6,3))+1.0E+0*F(2,1)*tt8+1.0E+0*tt4*(1.0E+&
&0*F(2,1)*C(5,5)+1.0E+0*F(2,2)*C(5,4)+1.0E+0*F(2,3)*C(5,3))+1.0E+0&
&*F(2,2)*tt11+1.0E+0*tt5*(1.0E+0*F(2,1)*C(4,5)+1.0E+0*F(2,2)*C(4,4&
&)+1.0E+0*F(2,3)*C(4,3))+1.0E+0*F(2,3)*tt12+5.0E-1*tt6*(1.0E+0*F(2&
&,1)*C(3,5)+1.0E+0*F(2,2)*C(3,4)+1.0E+0*F(2,3)*C(3,3))+5.0E-1*(1.0&
&E+0*F(2,1)*C(2,5)+1.0E+0*F(2,2)*C(2,4)+1.0E+0*C(2,3)*F(2,3))*tt2+&
&5.0E-1*(1.0E+0*C(1,3)*F(2,3)+1.0E+0*C(1,4)*F(2,2)+1.0E+0*C(1,5)*F&
&(2,1))*tt1)
jac(1,9) = 5.0E-1*(1.0E+0*tt3*(1.0E+0*F(3,1)*C(6,5)+1.0E+0*F(3,2)&
&*C(6,4)+1.0E+0*F(3,3)*C(6,3))+1.0E+0*F(3,1)*tt8+1.0E+0*tt4*(1.0E+&
&0*F(3,1)*C(5,5)+1.0E+0*F(3,2)*C(5,4)+1.0E+0*F(3,3)*C(5,3))+1.0E+0&
&*F(3,2)*tt11+1.0E+0*tt5*(1.0E+0*F(3,1)*C(4,5)+1.0E+0*F(3,2)*C(4,4&
&)+1.0E+0*F(3,3)*C(4,3))+1.0E+0*F(3,3)*tt12+5.0E-1*tt6*(1.0E+0*F(3&
&,1)*C(3,5)+1.0E+0*F(3,2)*C(3,4)+1.0E+0*C(3,3)*F(3,3))+5.0E-1*tt2*&
&(1.0E+0*C(2,3)*F(3,3)+1.0E+0*C(2,4)*F(3,2)+1.0E+0*C(2,5)*F(3,1))+&
&5.0E-1*tt1*(1.0E+0*C(1,3)*F(3,3)+1.0E+0*C(1,4)*F(3,2)+1.0E+0*C(1,&
&5)*F(3,1)))
END
SUBROUTINE &
&green_general_linear_elas_3d_hes(&
&  hes &
&, F &
&, C &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
REAL(KIND=8)  tt64
REAL(KIND=8)  tt65
REAL(KIND=8)  tt66
REAL(KIND=8)  tt67
REAL(KIND=8)  tt68
REAL(KIND=8)  tt69
REAL(KIND=8)  tt70
REAL(KIND=8)  tt71
REAL(KIND=8)  tt72
REAL(KIND=8)  tt73
REAL(KIND=8)  tt74
REAL(KIND=8)  tt75
REAL(KIND=8)  tt76
REAL(KIND=8)  tt77
REAL(KIND=8)  tt78
REAL(KIND=8)  tt79
REAL(KIND=8)  tt80
REAL(KIND=8)  tt81
REAL(KIND=8)  tt82
REAL(KIND=8)  tt83
REAL(KIND=8)  tt84
REAL(KIND=8)  tt85
REAL(KIND=8)  tt86
REAL(KIND=8)  tt87
REAL(KIND=8)  tt88
REAL(KIND=8)  tt89
REAL(KIND=8)  tt90
REAL(KIND=8)  tt91
REAL(KIND=8)  tt92
REAL(KIND=8)  tt93
REAL(KIND=8)  tt94
REAL(KIND=8)  tt95
REAL(KIND=8)  tt96
REAL(KIND=8)  tt97
REAL(KIND=8)  tt98
REAL(KIND=8)  tt99
REAL(KIND=8)  tt100
REAL(KIND=8)  tt101
REAL(KIND=8)  tt102
REAL(KIND=8)  tt103
REAL(KIND=8)  tt104
REAL(KIND=8)  tt105
REAL(KIND=8)  tt106
REAL(KIND=8)  tt107
REAL(KIND=8)  tt108
REAL(KIND=8)  tt109
REAL(KIND=8)  tt110
REAL(KIND=8)  tt111
REAL(KIND=8)  tt112
REAL(KIND=8)  tt113
REAL(KIND=8)  tt114
REAL(KIND=8)  tt115
REAL(KIND=8)  tt116
REAL(KIND=8)  tt117
REAL(KIND=8)  tt118
REAL(KIND=8)  tt119
REAL(KIND=8)  tt120
REAL(KIND=8)  tt121
REAL(KIND=8)  tt122
REAL(KIND=8)  tt123
REAL(KIND=8)  tt124
REAL(KIND=8)  tt125
REAL(KIND=8)  tt126
REAL(KIND=8)  tt127
REAL(KIND=8)  tt128
REAL(KIND=8)  tt129
REAL(KIND=8)  tt130
REAL(KIND=8)  tt131
REAL(KIND=8)  tt132
REAL(KIND=8)  tt133
REAL(KIND=8)  tt134
REAL(KIND=8)  tt135
REAL(KIND=8)  tt136
REAL(KIND=8)  tt137
REAL(KIND=8)  tt138
tt1 = 1.0E+0*F(1,2)*C(1,6)+1.0E+0*F(1,3)*C(1,5)+1.0E+0*C(1,1)*F(1&
&,1)
tt2 = F(3,1)**2+F(2,1)**2+F(1,1)**2-1
tt3 = 5.0E-1*C(1,1)*tt2
tt4 = F(3,2)**2+F(2,2)**2+F(1,2)**2-1
tt5 = 5.0E-1*C(2,1)*tt4
tt6 = F(3,3)**2+F(2,3)**2+F(1,3)**2-1
tt7 = 5.0E-1*C(3,1)*tt6
tt8 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt9 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt10 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt11 = 1.0E+0*(5.0E-1*C(1,3)*tt6+1.0E+0*C(1,4)*tt10+1.0E+0*C(1,5)&
&*tt9+5.0E-1*C(1,2)*tt4+1.0E+0*C(1,6)*tt8+tt3)
tt12 = 1.0E+0*tt10*C(4,1)
tt13 = 1.0E+0*tt9*C(5,1)
tt14 = 1.0E+0*F(1,2)*C(5,6)+1.0E+0*F(1,3)*C(5,5)+1.0E+0*F(1,1)*C(&
&5,1)
tt15 = 1.0E+0*tt8*C(6,1)
tt16 = 1.0E+0*F(1,2)*C(6,6)+1.0E+0*F(1,3)*C(6,5)+1.0E+0*F(1,1)*C(&
&6,1)
tt17 = 1.0E+0*C(1,5)*F(2,3)+1.0E+0*C(1,6)*F(2,2)+1.0E+0*C(1,1)*F(&
&2,1)
tt18 = 1.0E+0*F(2,2)*C(5,6)+1.0E+0*F(2,3)*C(5,5)+1.0E+0*F(2,1)*C(&
&5,1)
tt19 = 1.0E+0*F(2,2)*C(6,6)+1.0E+0*F(2,3)*C(6,5)+1.0E+0*F(2,1)*C(&
&6,1)
tt20 = 5.0E-1*(1.0E+0*F(1,2)*tt19+1.0E+0*F(2,2)*tt16+1.0E+0*F(1,3&
&)*tt18+1.0E+0*F(2,3)*tt14+1.0E+0*F(1,1)*tt17+1.0E+0*tt1*F(2,1))
tt21 = 1.0E+0*C(1,5)*F(3,3)+1.0E+0*C(1,6)*F(3,2)+1.0E+0*C(1,1)*F(&
&3,1)
tt22 = 1.0E+0*F(3,2)*C(5,6)+1.0E+0*F(3,3)*C(5,5)+1.0E+0*F(3,1)*C(&
&5,1)
tt23 = 1.0E+0*F(3,2)*C(6,6)+1.0E+0*F(3,3)*C(6,5)+1.0E+0*F(3,1)*C(&
&6,1)
tt24 = 5.0E-1*(1.0E+0*F(1,2)*tt23+1.0E+0*F(3,2)*tt16+1.0E+0*F(1,3&
&)*tt22+1.0E+0*F(3,3)*tt14+1.0E+0*F(1,1)*tt21+1.0E+0*tt1*F(3,1))
tt25 = 1.0E+0*F(1,1)*C(1,6)+1.0E+0*F(1,3)*C(1,4)+1.0E+0*C(1,2)*F(&
&1,2)
tt26 = 1.0E+0*F(1,2)*C(2,6)+1.0E+0*F(1,3)*C(2,5)+1.0E+0*F(1,1)*C(&
&2,1)
tt27 = 5.0E-1*C(1,6)*tt2
tt28 = 5.0E-1*C(2,6)*tt4
tt29 = 5.0E-1*tt6*C(3,6)
tt30 = 1.0E+0*tt10*C(4,6)
tt31 = 1.0E+0*F(1,2)*C(4,6)+1.0E+0*F(1,3)*C(4,5)+1.0E+0*F(1,1)*C(&
&4,1)
tt32 = 1.0E+0*tt9*C(5,6)
tt33 = 1.0E+0*F(1,1)*C(5,6)+1.0E+0*F(1,3)*C(5,4)+1.0E+0*F(1,2)*C(&
&5,2)
tt34 = 1.0E+0*tt8*C(6,6)
tt35 = 1.0E+0*F(1,1)*C(6,6)+1.0E+0*F(1,3)*C(6,4)+1.0E+0*F(1,2)*C(&
&6,2)
tt36 = 1.0E+0*(tt34+1.0E+0*tt9*C(6,5)+1.0E+0*tt10*C(6,4)+5.0E-1*t&
&t6*C(6,3)+5.0E-1*tt4*C(6,2)+5.0E-1*tt2*C(6,1))
tt37 = 5.0E-1*(tt36+1.0E+0*F(1,1)*tt16+1.0E+0*F(1,2)*tt35+tt34+1.&
&0E+0*F(1,3)*tt33+tt32+1.0E+0*F(1,3)*tt31+tt30+tt29+tt28+tt27+1.0E&
&+0*F(1,2)*tt26+1.0E+0*F(1,1)*tt25)
tt38 = 1.0E+0*C(1,4)*F(2,3)+1.0E+0*C(1,2)*F(2,2)+1.0E+0*C(1,6)*F(&
&2,1)
tt39 = 1.0E+0*F(2,1)*C(5,6)+1.0E+0*F(2,3)*C(5,4)+1.0E+0*F(2,2)*C(&
&5,2)
tt40 = 1.0E+0*F(2,1)*C(6,6)+1.0E+0*F(2,3)*C(6,4)+1.0E+0*F(2,2)*C(&
&6,2)
tt41 = 5.0E-1*(1.0E+0*F(1,2)*tt40+1.0E+0*F(2,1)*tt16+1.0E+0*F(1,3&
&)*tt39+1.0E+0*F(2,3)*tt31+1.0E+0*F(2,2)*tt26+1.0E+0*F(1,1)*tt38)
tt42 = 1.0E+0*C(1,4)*F(3,3)+1.0E+0*C(1,2)*F(3,2)+1.0E+0*C(1,6)*F(&
&3,1)
tt43 = 1.0E+0*F(3,1)*C(5,6)+1.0E+0*F(3,3)*C(5,4)+1.0E+0*F(3,2)*C(&
&5,2)
tt44 = 1.0E+0*F(3,1)*C(6,6)+1.0E+0*F(3,3)*C(6,4)+1.0E+0*F(3,2)*C(&
&6,2)
tt45 = 5.0E-1*(1.0E+0*F(1,2)*tt44+1.0E+0*F(3,1)*tt16+1.0E+0*F(1,3&
&)*tt43+1.0E+0*F(3,3)*tt31+1.0E+0*F(1,1)*tt42+1.0E+0*tt26*F(3,2))
tt46 = 1.0E+0*F(1,1)*C(1,5)+1.0E+0*F(1,2)*C(1,4)+1.0E+0*C(1,3)*F(&
&1,3)
tt47 = 5.0E-1*C(1,5)*tt2
tt48 = 5.0E-1*C(2,5)*tt4
tt49 = 5.0E-1*tt6*C(3,5)
tt50 = 1.0E+0*F(1,2)*C(3,6)+1.0E+0*F(1,3)*C(3,5)+1.0E+0*F(1,1)*C(&
&3,1)
tt51 = 1.0E+0*tt10*C(4,5)
tt52 = 1.0E+0*tt9*C(5,5)
tt53 = 1.0E+0*F(1,1)*C(5,5)+1.0E+0*F(1,2)*C(5,4)+1.0E+0*F(1,3)*C(&
&5,3)
tt54 = 1.0E+0*(1.0E+0*tt8*C(5,6)+tt52+1.0E+0*tt10*C(5,4)+5.0E-1*t&
&t6*C(5,3)+5.0E-1*tt4*C(5,2)+5.0E-1*tt2*C(5,1))
tt55 = 1.0E+0*tt8*C(6,5)
tt56 = 1.0E+0*F(1,1)*C(6,5)+1.0E+0*F(1,2)*C(6,4)+1.0E+0*F(1,3)*C(&
&6,3)
tt57 = 5.0E-1*(1.0E+0*F(1,2)*tt56+tt55+tt54+1.0E+0*F(1,1)*tt14+1.&
&0E+0*F(1,3)*tt53+tt52+1.0E+0*F(1,2)*tt31+tt51+1.0E+0*F(1,3)*tt50+&
&tt49+tt48+tt47+1.0E+0*F(1,1)*tt46)
tt58 = 1.0E+0*C(1,3)*F(2,3)+1.0E+0*C(1,4)*F(2,2)+1.0E+0*C(1,5)*F(&
&2,1)
tt59 = 1.0E+0*F(2,1)*C(5,5)+1.0E+0*F(2,2)*C(5,4)+1.0E+0*F(2,3)*C(&
&5,3)
tt60 = 1.0E+0*F(2,1)*C(6,5)+1.0E+0*F(2,2)*C(6,4)+1.0E+0*F(2,3)*C(&
&6,3)
tt61 = 5.0E-1*(1.0E+0*F(1,2)*tt60+1.0E+0*F(2,1)*tt14+1.0E+0*F(1,3&
&)*tt59+1.0E+0*F(2,2)*tt31+1.0E+0*F(2,3)*tt50+1.0E+0*F(1,1)*tt58)
tt62 = 1.0E+0*C(1,3)*F(3,3)+1.0E+0*C(1,4)*F(3,2)+1.0E+0*C(1,5)*F(&
&3,1)
tt63 = 1.0E+0*F(3,1)*C(5,5)+1.0E+0*F(3,2)*C(5,4)+1.0E+0*F(3,3)*C(&
&5,3)
tt64 = 1.0E+0*F(3,1)*C(6,5)+1.0E+0*F(3,2)*C(6,4)+1.0E+0*F(3,3)*C(&
&6,3)
tt65 = 5.0E-1*(1.0E+0*F(1,2)*tt64+1.0E+0*F(3,1)*tt14+1.0E+0*F(1,3&
&)*tt63+1.0E+0*F(3,2)*tt31+1.0E+0*F(3,3)*tt50+1.0E+0*F(1,1)*tt62)
tt66 = 5.0E-1*(1.0E+0*F(2,2)*tt23+1.0E+0*F(3,2)*tt19+1.0E+0*F(2,3&
&)*tt22+1.0E+0*F(3,3)*tt18+1.0E+0*F(2,1)*tt21+1.0E+0*tt17*F(3,1))
tt67 = 1.0E+0*F(2,2)*C(2,6)+1.0E+0*F(2,3)*C(2,5)+1.0E+0*C(2,1)*F(&
&2,1)
tt68 = 1.0E+0*F(2,2)*C(4,6)+1.0E+0*F(2,3)*C(4,5)+1.0E+0*F(2,1)*C(&
&4,1)
tt69 = 5.0E-1*(1.0E+0*F(1,1)*tt19+1.0E+0*F(2,2)*tt35+1.0E+0*F(2,3&
&)*tt33+1.0E+0*F(1,3)*tt68+1.0E+0*F(1,2)*tt67+1.0E+0*tt25*F(2,1))
tt70 = 5.0E-1*(tt36+1.0E+0*F(2,1)*tt19+1.0E+0*F(2,2)*tt40+tt34+1.&
&0E+0*F(2,3)*tt39+tt32+1.0E+0*F(2,3)*tt68+tt30+tt29+tt28+tt27+1.0E&
&+0*F(2,2)*tt67+1.0E+0*F(2,1)*tt38)
tt71 = 5.0E-1*(1.0E+0*F(2,2)*tt44+1.0E+0*F(3,1)*tt19+1.0E+0*F(2,3&
&)*tt43+1.0E+0*F(3,3)*tt68+1.0E+0*F(2,1)*tt42+1.0E+0*tt67*F(3,2))
tt72 = 1.0E+0*F(2,2)*C(3,6)+1.0E+0*F(2,3)*C(3,5)+1.0E+0*F(2,1)*C(&
&3,1)
tt73 = 5.0E-1*(1.0E+0*F(2,2)*tt56+1.0E+0*F(1,1)*tt18+1.0E+0*F(2,3&
&)*tt53+1.0E+0*F(1,2)*tt68+1.0E+0*F(1,3)*tt72+1.0E+0*tt46*F(2,1))
tt74 = 5.0E-1*(1.0E+0*F(2,2)*tt60+tt55+tt54+1.0E+0*F(2,1)*tt18+1.&
&0E+0*F(2,3)*tt59+tt52+1.0E+0*F(2,2)*tt68+tt51+1.0E+0*F(2,3)*tt72+&
&tt49+tt48+tt47+1.0E+0*F(2,1)*tt58)
tt75 = 5.0E-1*(1.0E+0*F(2,2)*tt64+1.0E+0*F(3,1)*tt18+1.0E+0*F(2,3&
&)*tt63+1.0E+0*F(3,2)*tt68+1.0E+0*F(3,3)*tt72+1.0E+0*F(2,1)*tt62)
tt76 = 1.0E+0*C(2,5)*F(3,3)+1.0E+0*C(2,6)*F(3,2)+1.0E+0*C(2,1)*F(&
&3,1)
tt77 = 1.0E+0*F(3,2)*C(4,6)+1.0E+0*F(3,3)*C(4,5)+1.0E+0*F(3,1)*C(&
&4,1)
tt78 = 5.0E-1*(1.0E+0*F(1,1)*tt23+1.0E+0*F(3,2)*tt35+1.0E+0*F(3,3&
&)*tt33+1.0E+0*F(1,3)*tt77+1.0E+0*F(1,2)*tt76+1.0E+0*tt25*F(3,1))
tt79 = 5.0E-1*(1.0E+0*F(2,1)*tt23+1.0E+0*F(3,2)*tt40+1.0E+0*F(3,3&
&)*tt39+1.0E+0*F(2,3)*tt77+1.0E+0*F(2,2)*tt76+1.0E+0*tt38*F(3,1))
tt80 = 5.0E-1*(tt36+1.0E+0*F(3,1)*tt23+1.0E+0*F(3,2)*tt44+tt34+1.&
&0E+0*F(3,3)*tt43+tt32+1.0E+0*F(3,3)*tt77+tt30+tt29+1.0E+0*F(3,2)*&
&tt76+1.0E+0*F(3,1)*tt42+tt28+tt27)
tt81 = 1.0E+0*F(3,2)*C(3,6)+1.0E+0*F(3,3)*C(3,5)+1.0E+0*C(3,1)*F(&
&3,1)
tt82 = 5.0E-1*(1.0E+0*F(3,2)*tt56+1.0E+0*F(1,1)*tt22+1.0E+0*F(3,3&
&)*tt53+1.0E+0*F(1,2)*tt77+1.0E+0*F(1,3)*tt81+1.0E+0*tt46*F(3,1))
tt83 = 5.0E-1*(1.0E+0*F(3,2)*tt60+1.0E+0*F(2,1)*tt22+1.0E+0*F(3,3&
&)*tt59+1.0E+0*F(2,2)*tt77+1.0E+0*F(2,3)*tt81+1.0E+0*tt58*F(3,1))
tt84 = 5.0E-1*(1.0E+0*F(3,2)*tt64+tt55+tt54+1.0E+0*F(3,1)*tt22+1.&
&0E+0*F(3,3)*tt63+tt52+1.0E+0*F(3,2)*tt77+tt51+1.0E+0*F(3,3)*tt81+&
&tt49+1.0E+0*F(3,1)*tt62+tt48+tt47)
tt85 = 1.0E+0*F(1,1)*C(2,6)+1.0E+0*F(1,3)*C(2,4)+1.0E+0*F(1,2)*C(&
&2,2)
tt86 = 5.0E-1*C(1,2)*tt2
tt87 = 5.0E-1*C(2,2)*tt4
tt88 = 5.0E-1*C(3,2)*tt6
tt89 = 1.0E+0*(5.0E-1*C(2,3)*tt6+1.0E+0*C(2,4)*tt10+1.0E+0*C(2,5)&
&*tt9+tt87+1.0E+0*C(2,6)*tt8+5.0E-1*C(2,1)*tt2)
tt90 = 1.0E+0*tt10*C(4,2)
tt91 = 1.0E+0*F(1,1)*C(4,6)+1.0E+0*F(1,3)*C(4,4)+1.0E+0*F(1,2)*C(&
&4,2)
tt92 = 1.0E+0*tt9*C(5,2)
tt93 = 1.0E+0*tt8*C(6,2)
tt94 = 1.0E+0*F(2,1)*C(2,6)+1.0E+0*F(2,3)*C(2,4)+1.0E+0*C(2,2)*F(&
&2,2)
tt95 = 1.0E+0*F(2,1)*C(4,6)+1.0E+0*F(2,3)*C(4,4)+1.0E+0*F(2,2)*C(&
&4,2)
tt96 = 5.0E-1*(1.0E+0*F(1,1)*tt40+1.0E+0*F(2,1)*tt35+1.0E+0*F(1,3&
&)*tt95+1.0E+0*F(2,3)*tt91+1.0E+0*F(1,2)*tt94+1.0E+0*F(2,2)*tt85)
tt97 = 1.0E+0*C(2,4)*F(3,3)+1.0E+0*C(2,2)*F(3,2)+1.0E+0*C(2,6)*F(&
&3,1)
tt98 = 1.0E+0*F(3,1)*C(4,6)+1.0E+0*F(3,3)*C(4,4)+1.0E+0*F(3,2)*C(&
&4,2)
tt99 = 5.0E-1*(1.0E+0*F(1,1)*tt44+1.0E+0*F(3,1)*tt35+1.0E+0*F(1,3&
&)*tt98+1.0E+0*F(3,3)*tt91+1.0E+0*F(1,2)*tt97+1.0E+0*tt85*F(3,2))
tt100 = 1.0E+0*F(1,1)*C(2,5)+1.0E+0*F(1,2)*C(2,4)+1.0E+0*F(1,3)*C&
&(2,3)
tt101 = 5.0E-1*C(1,4)*tt2
tt102 = 5.0E-1*C(2,4)*tt4
tt103 = 5.0E-1*tt6*C(3,4)
tt104 = 1.0E+0*F(1,1)*C(3,6)+1.0E+0*F(1,3)*C(3,4)+1.0E+0*F(1,2)*C&
&(3,2)
tt105 = 1.0E+0*tt10*C(4,4)
tt106 = 1.0E+0*F(1,1)*C(4,5)+1.0E+0*F(1,2)*C(4,4)+1.0E+0*F(1,3)*C&
&(4,3)
tt107 = 1.0E+0*(1.0E+0*tt8*C(4,6)+1.0E+0*tt9*C(4,5)+tt105+5.0E-1*&
&tt6*C(4,3)+5.0E-1*tt4*C(4,2)+5.0E-1*tt2*C(4,1))
tt108 = 1.0E+0*tt9*C(5,4)
tt109 = 1.0E+0*tt8*C(6,4)
tt110 = 5.0E-1*(1.0E+0*F(1,1)*tt56+tt109+1.0E+0*F(1,1)*tt33+tt108&
&+tt107+1.0E+0*F(1,2)*tt91+1.0E+0*F(1,3)*tt106+tt105+1.0E+0*F(1,3)&
&*tt104+tt103+tt102+tt101+1.0E+0*F(1,2)*tt100)
tt111 = 1.0E+0*F(2,1)*C(2,5)+1.0E+0*F(2,2)*C(2,4)+1.0E+0*C(2,3)*F&
&(2,3)
tt112 = 1.0E+0*F(2,1)*C(4,5)+1.0E+0*F(2,2)*C(4,4)+1.0E+0*F(2,3)*C&
&(4,3)
tt113 = 5.0E-1*(1.0E+0*F(1,1)*tt60+1.0E+0*F(2,1)*tt33+1.0E+0*F(2,&
&2)*tt91+1.0E+0*F(1,3)*tt112+1.0E+0*F(2,3)*tt104+1.0E+0*F(1,2)*tt1&
&11)
tt114 = 1.0E+0*C(2,3)*F(3,3)+1.0E+0*C(2,4)*F(3,2)+1.0E+0*C(2,5)*F&
&(3,1)
tt115 = 1.0E+0*F(3,1)*C(4,5)+1.0E+0*F(3,2)*C(4,4)+1.0E+0*F(3,3)*C&
&(4,3)
tt116 = 5.0E-1*(1.0E+0*F(1,1)*tt64+1.0E+0*F(3,1)*tt33+1.0E+0*F(3,&
&2)*tt91+1.0E+0*F(1,3)*tt115+1.0E+0*F(3,3)*tt104+1.0E+0*F(1,2)*tt1&
&14)
tt117 = 5.0E-1*(1.0E+0*F(2,1)*tt44+1.0E+0*F(3,1)*tt40+1.0E+0*F(2,&
&3)*tt98+1.0E+0*F(3,3)*tt95+1.0E+0*F(2,2)*tt97+1.0E+0*tt94*F(3,2))
tt118 = 1.0E+0*F(2,1)*C(3,6)+1.0E+0*F(2,3)*C(3,4)+1.0E+0*F(2,2)*C&
&(3,2)
tt119 = 5.0E-1*(1.0E+0*F(2,1)*tt56+1.0E+0*F(1,1)*tt39+1.0E+0*F(1,&
&2)*tt95+1.0E+0*F(2,3)*tt106+1.0E+0*F(1,3)*tt118+1.0E+0*F(2,2)*tt1&
&00)
tt120 = 5.0E-1*(1.0E+0*F(2,1)*tt60+tt109+1.0E+0*F(2,1)*tt39+tt108&
&+tt107+1.0E+0*F(2,2)*tt95+1.0E+0*F(2,3)*tt112+tt105+1.0E+0*F(2,3)&
&*tt118+tt103+tt102+tt101+1.0E+0*F(2,2)*tt111)
tt121 = 5.0E-1*(1.0E+0*F(2,1)*tt64+1.0E+0*F(3,1)*tt39+1.0E+0*F(3,&
&2)*tt95+1.0E+0*F(2,3)*tt115+1.0E+0*F(3,3)*tt118+1.0E+0*F(2,2)*tt1&
&14)
tt122 = 1.0E+0*F(3,1)*C(3,6)+1.0E+0*F(3,3)*C(3,4)+1.0E+0*C(3,2)*F&
&(3,2)
tt123 = 5.0E-1*(1.0E+0*F(3,1)*tt56+1.0E+0*F(1,1)*tt43+1.0E+0*F(1,&
&2)*tt98+1.0E+0*F(3,3)*tt106+1.0E+0*F(1,3)*tt122+1.0E+0*tt100*F(3,&
&2))
tt124 = 5.0E-1*(1.0E+0*F(3,1)*tt60+1.0E+0*F(2,1)*tt43+1.0E+0*F(2,&
&2)*tt98+1.0E+0*F(3,3)*tt112+1.0E+0*F(2,3)*tt122+1.0E+0*tt111*F(3,&
&2))
tt125 = 5.0E-1*(1.0E+0*F(3,1)*tt64+tt109+1.0E+0*F(3,1)*tt43+tt108&
&+tt107+1.0E+0*F(3,2)*tt98+1.0E+0*F(3,3)*tt115+tt105+1.0E+0*F(3,3)&
&*tt122+tt103+1.0E+0*F(3,2)*tt114+tt102+tt101)
tt126 = 5.0E-1*C(1,3)*tt2
tt127 = 5.0E-1*C(2,3)*tt4
tt128 = 5.0E-1*C(3,3)*tt6
tt129 = 1.0E+0*F(1,1)*C(3,5)+1.0E+0*F(1,2)*C(3,4)+1.0E+0*F(1,3)*C&
&(3,3)
tt130 = 1.0E+0*(1.0E+0*tt8*C(3,6)+1.0E+0*tt9*C(3,5)+1.0E+0*tt10*C&
&(3,4)+tt128+5.0E-1*C(3,2)*tt4+5.0E-1*C(3,1)*tt2)
tt131 = 1.0E+0*tt10*C(4,3)
tt132 = 1.0E+0*tt9*C(5,3)
tt133 = 1.0E+0*tt8*C(6,3)
tt134 = 1.0E+0*F(2,1)*C(3,5)+1.0E+0*F(2,2)*C(3,4)+1.0E+0*F(2,3)*C&
&(3,3)
tt135 = 5.0E-1*(1.0E+0*F(1,1)*tt59+1.0E+0*F(2,1)*tt53+1.0E+0*F(1,&
&2)*tt112+1.0E+0*F(2,2)*tt106+1.0E+0*F(1,3)*tt134+1.0E+0*F(2,3)*tt&
&129)
tt136 = 1.0E+0*F(3,1)*C(3,5)+1.0E+0*F(3,2)*C(3,4)+1.0E+0*C(3,3)*F&
&(3,3)
tt137 = 5.0E-1*(1.0E+0*F(1,1)*tt63+1.0E+0*F(3,1)*tt53+1.0E+0*F(1,&
&2)*tt115+1.0E+0*F(3,2)*tt106+1.0E+0*F(1,3)*tt136+1.0E+0*F(3,3)*tt&
&129)
tt138 = 5.0E-1*(1.0E+0*F(2,1)*tt63+1.0E+0*F(3,1)*tt59+1.0E+0*F(2,&
&2)*tt115+1.0E+0*F(3,2)*tt112+1.0E+0*F(2,3)*tt136+1.0E+0*F(3,3)*tt&
&134)
hes(1,1) = 5.0E-1*(2.0E+0*F(1,2)*tt16+tt15+2.0E+0*F(1,3)*tt14+tt1&
&3+tt12+tt11+tt7+tt5+tt3+2.0E+0*F(1,1)*tt1)
hes(1,2) = tt20
hes(1,3) = tt24
hes(1,4) = tt37
hes(1,5) = tt41
hes(1,6) = tt45
hes(1,7) = tt57
hes(1,8) = tt61
hes(1,9) = tt65
hes(2,1) = tt20
hes(2,2) = 5.0E-1*(2.0E+0*F(2,2)*tt19+tt15+2.0E+0*F(2,3)*tt18+tt1&
&3+tt12+tt11+tt7+tt5+tt3+2.0E+0*F(2,1)*tt17)
hes(2,3) = tt66
hes(2,4) = tt69
hes(2,5) = tt70
hes(2,6) = tt71
hes(2,7) = tt73
hes(2,8) = tt74
hes(2,9) = tt75
hes(3,1) = tt24
hes(3,2) = tt66
hes(3,3) = 5.0E-1*(2.0E+0*F(3,2)*tt23+tt15+2.0E+0*F(3,3)*tt22+tt1&
&3+tt12+tt11+tt7+2.0E+0*F(3,1)*tt21+tt5+tt3)
hes(3,4) = tt78
hes(3,5) = tt79
hes(3,6) = tt80
hes(3,7) = tt82
hes(3,8) = tt83
hes(3,9) = tt84
hes(4,1) = tt37
hes(4,2) = tt69
hes(4,3) = tt78
hes(4,4) = 5.0E-1*(2.0E+0*F(1,1)*tt35+tt93+tt92+2.0E+0*F(1,3)*tt9&
&1+tt90+tt89+tt88+tt87+tt86+2.0E+0*F(1,2)*tt85)
hes(4,5) = tt96
hes(4,6) = tt99
hes(4,7) = tt110
hes(4,8) = tt113
hes(4,9) = tt116
hes(5,1) = tt41
hes(5,2) = tt70
hes(5,3) = tt79
hes(5,4) = tt96
hes(5,5) = 5.0E-1*(2.0E+0*F(2,1)*tt40+tt93+tt92+2.0E+0*F(2,3)*tt9&
&5+tt90+tt89+tt88+tt87+tt86+2.0E+0*F(2,2)*tt94)
hes(5,6) = tt117
hes(5,7) = tt119
hes(5,8) = tt120
hes(5,9) = tt121
hes(6,1) = tt45
hes(6,2) = tt71
hes(6,3) = tt80
hes(6,4) = tt99
hes(6,5) = tt117
hes(6,6) = 5.0E-1*(2.0E+0*F(3,1)*tt44+tt93+tt92+2.0E+0*F(3,3)*tt9&
&8+tt90+tt89+tt88+2.0E+0*F(3,2)*tt97+tt87+tt86)
hes(6,7) = tt123
hes(6,8) = tt124
hes(6,9) = tt125
hes(7,1) = tt57
hes(7,2) = tt73
hes(7,3) = tt82
hes(7,4) = tt110
hes(7,5) = tt119
hes(7,6) = tt123
hes(7,7) = 5.0E-1*(tt133+2.0E+0*F(1,1)*tt53+tt132+2.0E+0*F(1,2)*t&
&t106+tt131+tt130+2.0E+0*F(1,3)*tt129+tt128+tt127+tt126)
hes(7,8) = tt135
hes(7,9) = tt137
hes(8,1) = tt61
hes(8,2) = tt74
hes(8,3) = tt83
hes(8,4) = tt113
hes(8,5) = tt120
hes(8,6) = tt124
hes(8,7) = tt135
hes(8,8) = 5.0E-1*(tt133+2.0E+0*F(2,1)*tt59+tt132+2.0E+0*F(2,2)*t&
&t112+tt131+tt130+2.0E+0*F(2,3)*tt134+tt128+tt127+tt126)
hes(8,9) = tt138
hes(9,1) = tt65
hes(9,2) = tt75
hes(9,3) = tt84
hes(9,4) = tt116
hes(9,5) = tt121
hes(9,6) = tt125
hes(9,7) = tt137
hes(9,8) = tt138
hes(9,9) = 5.0E-1*(tt133+2.0E+0*F(3,1)*tt63+tt132+2.0E+0*F(3,2)*t&
&t115+tt131+tt130+2.0E+0*F(3,3)*tt136+tt128+tt127+tt126)
END
SUBROUTINE &
&coro_general_linear_elas_3d_val(&
&  val &
&, F &
&, C &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
REAL(KIND=8) R(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = 5.0E-1*(2*F(3,1)*R(3,1)+2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-1
tt2 = F(3,1)*R(3,2)+R(3,1)*F(3,2)+F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1&
&,1)*R(1,2)+R(1,1)*F(1,2)
tt3 = 5.0E-1*(2*F(3,2)*R(3,2)+2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))-1
tt4 = F(3,1)*R(3,3)+R(3,1)*F(3,3)+F(2,1)*R(2,3)+R(2,1)*F(2,3)+F(1&
&,1)*R(1,3)+R(1,1)*F(1,3)
tt5 = F(3,2)*R(3,3)+R(3,2)*F(3,3)+F(2,2)*R(2,3)+R(2,2)*F(2,3)+F(1&
&,2)*R(1,3)+R(1,2)*F(1,3)
tt6 = 5.0E-1*(2*F(3,3)*R(3,3)+2*F(2,3)*R(2,3)+2*F(1,3)*R(1,3))-1
val(1,1) = 5.0E-1*(1.0E+0*tt2*(1.0E+0*tt2*C(6,6)+1.0E+0*tt4*C(6,5&
&)+1.0E+0*tt5*C(6,4)+tt6*C(6,3)+tt3*C(6,2)+tt1*C(6,1))+1.0E+0*tt4*&
&(1.0E+0*tt2*C(5,6)+1.0E+0*tt4*C(5,5)+1.0E+0*tt5*C(5,4)+tt6*C(5,3)&
&+tt3*C(5,2)+tt1*C(5,1))+1.0E+0*tt5*(1.0E+0*tt2*C(4,6)+1.0E+0*tt4*&
&C(4,5)+1.0E+0*tt5*C(4,4)+tt6*C(4,3)+tt3*C(4,2)+tt1*C(4,1))+tt6*(1&
&.0E+0*tt2*C(3,6)+1.0E+0*tt4*C(3,5)+1.0E+0*tt5*C(3,4)+C(3,3)*tt6+C&
&(3,2)*tt3+C(3,1)*tt1)+tt3*(C(2,3)*tt6+1.0E+0*C(2,4)*tt5+1.0E+0*C(&
&2,5)*tt4+C(2,2)*tt3+1.0E+0*C(2,6)*tt2+C(2,1)*tt1)+tt1*(C(1,3)*tt6&
&+1.0E+0*C(1,4)*tt5+1.0E+0*C(1,5)*tt4+C(1,2)*tt3+1.0E+0*C(1,6)*tt2&
&+C(1,1)*tt1))
END
SUBROUTINE &
&coro_general_linear_elas_3d_jac(&
&  jac &
&, F &
&, C &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
REAL(KIND=8) R(3, 3)
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
tt1 = 5.0E-1*(2*F(3,1)*R(3,1)+2*F(2,1)*R(2,1)+2*F(1,1)*R(1,1))-1
tt2 = 5.0E-1*(2*F(3,2)*R(3,2)+2*F(2,2)*R(2,2)+2*F(1,2)*R(1,2))-1
tt3 = F(3,1)*R(3,2)+R(3,1)*F(3,2)+F(2,1)*R(2,2)+R(2,1)*F(2,2)+F(1&
&,1)*R(1,2)+R(1,1)*F(1,2)
tt4 = F(3,1)*R(3,3)+R(3,1)*F(3,3)+F(2,1)*R(2,3)+R(2,1)*F(2,3)+F(1&
&,1)*R(1,3)+R(1,1)*F(1,3)
tt5 = F(3,2)*R(3,3)+R(3,2)*F(3,3)+F(2,2)*R(2,3)+R(2,2)*F(2,3)+F(1&
&,2)*R(1,3)+R(1,2)*F(1,3)
tt6 = 5.0E-1*(2*F(3,3)*R(3,3)+2*F(2,3)*R(2,3)+2*F(1,3)*R(1,3))-1
tt7 = C(1,3)*tt6+1.0E+0*C(1,4)*tt5+1.0E+0*C(1,5)*tt4+C(1,2)*tt2+1&
&.0E+0*C(1,6)*tt3+C(1,1)*tt1
tt8 = 1.0E+0*tt3*C(5,6)+1.0E+0*tt4*C(5,5)+1.0E+0*tt5*C(5,4)+tt6*C&
&(5,3)+tt2*C(5,2)+tt1*C(5,1)
tt9 = 1.0E+0*tt3*C(6,6)+1.0E+0*tt4*C(6,5)+1.0E+0*tt5*C(6,4)+tt6*C&
&(6,3)+tt2*C(6,2)+tt1*C(6,1)
tt10 = C(2,3)*tt6+1.0E+0*C(2,4)*tt5+1.0E+0*C(2,5)*tt4+C(2,2)*tt2+&
&1.0E+0*C(2,6)*tt3+C(2,1)*tt1
tt11 = 1.0E+0*tt3*C(4,6)+1.0E+0*tt4*C(4,5)+1.0E+0*tt5*C(4,4)+tt6*&
&C(4,3)+tt2*C(4,2)+tt1*C(4,1)
tt12 = 1.0E+0*tt3*C(3,6)+1.0E+0*tt4*C(3,5)+1.0E+0*tt5*C(3,4)+C(3,&
&3)*tt6+C(3,2)*tt2+C(3,1)*tt1
jac(1,1) = 5.0E-1*(1.0E+0*R(1,2)*tt9+1.0E+0*tt3*(1.0E+0*R(1,2)*C(&
&6,6)+1.0E+0*R(1,3)*C(6,5)+1.0E+0*R(1,1)*C(6,1))+1.0E+0*R(1,3)*tt8&
&+1.0E+0*tt4*(1.0E+0*R(1,2)*C(5,6)+1.0E+0*R(1,3)*C(5,5)+1.0E+0*R(1&
&,1)*C(5,1))+1.0E+0*tt5*(1.0E+0*R(1,2)*C(4,6)+1.0E+0*R(1,3)*C(4,5)&
&+1.0E+0*R(1,1)*C(4,1))+tt6*(1.0E+0*R(1,2)*C(3,6)+1.0E+0*R(1,3)*C(&
&3,5)+1.0E+0*R(1,1)*C(3,1))+1.0E+0*R(1,1)*tt7+(1.0E+0*R(1,2)*C(2,6&
&)+1.0E+0*R(1,3)*C(2,5)+1.0E+0*R(1,1)*C(2,1))*tt2+(1.0E+0*R(1,2)*C&
&(1,6)+1.0E+0*R(1,3)*C(1,5)+1.0E+0*C(1,1)*R(1,1))*tt1)
jac(1,2) = 5.0E-1*(1.0E+0*R(2,2)*tt9+1.0E+0*tt3*(1.0E+0*R(2,2)*C(&
&6,6)+1.0E+0*R(2,3)*C(6,5)+1.0E+0*R(2,1)*C(6,1))+1.0E+0*R(2,3)*tt8&
&+1.0E+0*tt4*(1.0E+0*R(2,2)*C(5,6)+1.0E+0*R(2,3)*C(5,5)+1.0E+0*R(2&
&,1)*C(5,1))+1.0E+0*tt5*(1.0E+0*R(2,2)*C(4,6)+1.0E+0*R(2,3)*C(4,5)&
&+1.0E+0*R(2,1)*C(4,1))+tt6*(1.0E+0*R(2,2)*C(3,6)+1.0E+0*R(2,3)*C(&
&3,5)+1.0E+0*R(2,1)*C(3,1))+1.0E+0*R(2,1)*tt7+(1.0E+0*R(2,2)*C(2,6&
&)+1.0E+0*R(2,3)*C(2,5)+1.0E+0*C(2,1)*R(2,1))*tt2+(1.0E+0*C(1,5)*R&
&(2,3)+1.0E+0*C(1,6)*R(2,2)+1.0E+0*C(1,1)*R(2,1))*tt1)
jac(1,3) = 5.0E-1*(1.0E+0*R(3,2)*tt9+1.0E+0*tt3*(1.0E+0*R(3,2)*C(&
&6,6)+1.0E+0*R(3,3)*C(6,5)+1.0E+0*R(3,1)*C(6,1))+1.0E+0*R(3,3)*tt8&
&+1.0E+0*tt4*(1.0E+0*R(3,2)*C(5,6)+1.0E+0*R(3,3)*C(5,5)+1.0E+0*R(3&
&,1)*C(5,1))+1.0E+0*tt5*(1.0E+0*R(3,2)*C(4,6)+1.0E+0*R(3,3)*C(4,5)&
&+1.0E+0*R(3,1)*C(4,1))+tt6*(1.0E+0*R(3,2)*C(3,6)+1.0E+0*R(3,3)*C(&
&3,5)+1.0E+0*C(3,1)*R(3,1))+1.0E+0*R(3,1)*tt7+tt2*(1.0E+0*C(2,5)*R&
&(3,3)+1.0E+0*C(2,6)*R(3,2)+1.0E+0*C(2,1)*R(3,1))+tt1*(1.0E+0*C(1,&
&5)*R(3,3)+1.0E+0*C(1,6)*R(3,2)+1.0E+0*C(1,1)*R(3,1)))
jac(1,4) = 5.0E-1*(1.0E+0*R(1,1)*tt9+1.0E+0*tt3*(1.0E+0*R(1,1)*C(&
&6,6)+1.0E+0*R(1,3)*C(6,4)+1.0E+0*R(1,2)*C(6,2))+1.0E+0*tt4*(1.0E+&
&0*R(1,1)*C(5,6)+1.0E+0*R(1,3)*C(5,4)+1.0E+0*R(1,2)*C(5,2))+1.0E+0&
&*R(1,3)*tt11+1.0E+0*tt5*(1.0E+0*R(1,1)*C(4,6)+1.0E+0*R(1,3)*C(4,4&
&)+1.0E+0*R(1,2)*C(4,2))+tt6*(1.0E+0*R(1,1)*C(3,6)+1.0E+0*R(1,3)*C&
&(3,4)+1.0E+0*R(1,2)*C(3,2))+1.0E+0*R(1,2)*tt10+(1.0E+0*R(1,1)*C(2&
&,6)+1.0E+0*R(1,3)*C(2,4)+1.0E+0*R(1,2)*C(2,2))*tt2+(1.0E+0*R(1,1)&
&*C(1,6)+1.0E+0*R(1,3)*C(1,4)+1.0E+0*C(1,2)*R(1,2))*tt1)
jac(1,5) = 5.0E-1*(1.0E+0*R(2,1)*tt9+1.0E+0*tt3*(1.0E+0*R(2,1)*C(&
&6,6)+1.0E+0*R(2,3)*C(6,4)+1.0E+0*R(2,2)*C(6,2))+1.0E+0*tt4*(1.0E+&
&0*R(2,1)*C(5,6)+1.0E+0*R(2,3)*C(5,4)+1.0E+0*R(2,2)*C(5,2))+1.0E+0&
&*R(2,3)*tt11+1.0E+0*tt5*(1.0E+0*R(2,1)*C(4,6)+1.0E+0*R(2,3)*C(4,4&
&)+1.0E+0*R(2,2)*C(4,2))+tt6*(1.0E+0*R(2,1)*C(3,6)+1.0E+0*R(2,3)*C&
&(3,4)+1.0E+0*R(2,2)*C(3,2))+1.0E+0*R(2,2)*tt10+(1.0E+0*R(2,1)*C(2&
&,6)+1.0E+0*R(2,3)*C(2,4)+1.0E+0*C(2,2)*R(2,2))*tt2+(1.0E+0*C(1,4)&
&*R(2,3)+1.0E+0*C(1,2)*R(2,2)+1.0E+0*C(1,6)*R(2,1))*tt1)
jac(1,6) = 5.0E-1*(1.0E+0*R(3,1)*tt9+1.0E+0*tt3*(1.0E+0*R(3,1)*C(&
&6,6)+1.0E+0*R(3,3)*C(6,4)+1.0E+0*R(3,2)*C(6,2))+1.0E+0*tt4*(1.0E+&
&0*R(3,1)*C(5,6)+1.0E+0*R(3,3)*C(5,4)+1.0E+0*R(3,2)*C(5,2))+1.0E+0&
&*R(3,3)*tt11+1.0E+0*tt5*(1.0E+0*R(3,1)*C(4,6)+1.0E+0*R(3,3)*C(4,4&
&)+1.0E+0*R(3,2)*C(4,2))+tt6*(1.0E+0*R(3,1)*C(3,6)+1.0E+0*R(3,3)*C&
&(3,4)+1.0E+0*C(3,2)*R(3,2))+1.0E+0*R(3,2)*tt10+tt2*(1.0E+0*C(2,4)&
&*R(3,3)+1.0E+0*C(2,2)*R(3,2)+1.0E+0*C(2,6)*R(3,1))+tt1*(1.0E+0*C(&
&1,4)*R(3,3)+1.0E+0*C(1,2)*R(3,2)+1.0E+0*C(1,6)*R(3,1)))
jac(1,7) = 5.0E-1*(1.0E+0*tt3*(1.0E+0*R(1,1)*C(6,5)+1.0E+0*R(1,2)&
&*C(6,4)+1.0E+0*R(1,3)*C(6,3))+1.0E+0*R(1,1)*tt8+1.0E+0*tt4*(1.0E+&
&0*R(1,1)*C(5,5)+1.0E+0*R(1,2)*C(5,4)+1.0E+0*R(1,3)*C(5,3))+1.0E+0&
&*R(1,2)*tt11+1.0E+0*tt5*(1.0E+0*R(1,1)*C(4,5)+1.0E+0*R(1,2)*C(4,4&
&)+1.0E+0*R(1,3)*C(4,3))+1.0E+0*R(1,3)*tt12+tt6*(1.0E+0*R(1,1)*C(3&
&,5)+1.0E+0*R(1,2)*C(3,4)+1.0E+0*R(1,3)*C(3,3))+(1.0E+0*R(1,1)*C(2&
&,5)+1.0E+0*R(1,2)*C(2,4)+1.0E+0*R(1,3)*C(2,3))*tt2+(1.0E+0*R(1,1)&
&*C(1,5)+1.0E+0*R(1,2)*C(1,4)+1.0E+0*C(1,3)*R(1,3))*tt1)
jac(1,8) = 5.0E-1*(1.0E+0*tt3*(1.0E+0*R(2,1)*C(6,5)+1.0E+0*R(2,2)&
&*C(6,4)+1.0E+0*R(2,3)*C(6,3))+1.0E+0*R(2,1)*tt8+1.0E+0*tt4*(1.0E+&
&0*R(2,1)*C(5,5)+1.0E+0*R(2,2)*C(5,4)+1.0E+0*R(2,3)*C(5,3))+1.0E+0&
&*R(2,2)*tt11+1.0E+0*tt5*(1.0E+0*R(2,1)*C(4,5)+1.0E+0*R(2,2)*C(4,4&
&)+1.0E+0*R(2,3)*C(4,3))+1.0E+0*R(2,3)*tt12+tt6*(1.0E+0*R(2,1)*C(3&
&,5)+1.0E+0*R(2,2)*C(3,4)+1.0E+0*R(2,3)*C(3,3))+(1.0E+0*R(2,1)*C(2&
&,5)+1.0E+0*R(2,2)*C(2,4)+1.0E+0*C(2,3)*R(2,3))*tt2+(1.0E+0*C(1,3)&
&*R(2,3)+1.0E+0*C(1,4)*R(2,2)+1.0E+0*C(1,5)*R(2,1))*tt1)
jac(1,9) = 5.0E-1*(1.0E+0*tt3*(1.0E+0*R(3,1)*C(6,5)+1.0E+0*R(3,2)&
&*C(6,4)+1.0E+0*R(3,3)*C(6,3))+1.0E+0*R(3,1)*tt8+1.0E+0*tt4*(1.0E+&
&0*R(3,1)*C(5,5)+1.0E+0*R(3,2)*C(5,4)+1.0E+0*R(3,3)*C(5,3))+1.0E+0&
&*R(3,2)*tt11+1.0E+0*tt5*(1.0E+0*R(3,1)*C(4,5)+1.0E+0*R(3,2)*C(4,4&
&)+1.0E+0*R(3,3)*C(4,3))+1.0E+0*R(3,3)*tt12+tt6*(1.0E+0*R(3,1)*C(3&
&,5)+1.0E+0*R(3,2)*C(3,4)+1.0E+0*C(3,3)*R(3,3))+tt2*(1.0E+0*C(2,3)&
&*R(3,3)+1.0E+0*C(2,4)*R(3,2)+1.0E+0*C(2,5)*R(3,1))+tt1*(1.0E+0*C(&
&1,3)*R(3,3)+1.0E+0*C(1,4)*R(3,2)+1.0E+0*C(1,5)*R(3,1)))
END
SUBROUTINE &
&coro_general_linear_elas_3d_hes(&
&  hes &
&, F &
&, C &
&, R &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8) C(6, 6)
REAL(KIND=8) R(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
REAL(KIND=8)  tt64
REAL(KIND=8)  tt65
REAL(KIND=8)  tt66
REAL(KIND=8)  tt67
REAL(KIND=8)  tt68
REAL(KIND=8)  tt69
REAL(KIND=8)  tt70
REAL(KIND=8)  tt71
REAL(KIND=8)  tt72
REAL(KIND=8)  tt73
REAL(KIND=8)  tt74
REAL(KIND=8)  tt75
REAL(KIND=8)  tt76
REAL(KIND=8)  tt77
REAL(KIND=8)  tt78
REAL(KIND=8)  tt79
REAL(KIND=8)  tt80
REAL(KIND=8)  tt81
REAL(KIND=8)  tt82
REAL(KIND=8)  tt83
REAL(KIND=8)  tt84
REAL(KIND=8)  tt85
REAL(KIND=8)  tt86
REAL(KIND=8)  tt87
REAL(KIND=8)  tt88
REAL(KIND=8)  tt89
REAL(KIND=8)  tt90
tt1 = 1.0E+0*R(1,2)*C(1,6)+1.0E+0*R(1,3)*C(1,5)+1.0E+0*C(1,1)*R(1&
&,1)
tt2 = 1.0E+0*R(1,2)*C(5,6)+1.0E+0*R(1,3)*C(5,5)+1.0E+0*R(1,1)*C(5&
&,1)
tt3 = 1.0E+0*R(1,2)*C(6,6)+1.0E+0*R(1,3)*C(6,5)+1.0E+0*R(1,1)*C(6&
&,1)
tt4 = 1.0E+0*C(1,5)*R(2,3)+1.0E+0*C(1,6)*R(2,2)+1.0E+0*C(1,1)*R(2&
&,1)
tt5 = 1.0E+0*R(2,2)*C(5,6)+1.0E+0*R(2,3)*C(5,5)+1.0E+0*R(2,1)*C(5&
&,1)
tt6 = 1.0E+0*R(2,2)*C(6,6)+1.0E+0*R(2,3)*C(6,5)+1.0E+0*R(2,1)*C(6&
&,1)
tt7 = 5.0E-1*(1.0E+0*R(1,2)*tt6+1.0E+0*R(2,2)*tt3+1.0E+0*R(1,3)*t&
&t5+1.0E+0*R(2,3)*tt2+1.0E+0*R(1,1)*tt4+1.0E+0*tt1*R(2,1))
tt8 = 1.0E+0*C(1,5)*R(3,3)+1.0E+0*C(1,6)*R(3,2)+1.0E+0*C(1,1)*R(3&
&,1)
tt9 = 1.0E+0*R(3,2)*C(5,6)+1.0E+0*R(3,3)*C(5,5)+1.0E+0*R(3,1)*C(5&
&,1)
tt10 = 1.0E+0*R(3,2)*C(6,6)+1.0E+0*R(3,3)*C(6,5)+1.0E+0*R(3,1)*C(&
&6,1)
tt11 = 5.0E-1*(1.0E+0*R(1,2)*tt10+1.0E+0*R(3,2)*tt3+1.0E+0*R(1,3)&
&*tt9+1.0E+0*R(3,3)*tt2+1.0E+0*R(1,1)*tt8+1.0E+0*tt1*R(3,1))
tt12 = 1.0E+0*R(1,1)*C(1,6)+1.0E+0*R(1,3)*C(1,4)+1.0E+0*C(1,2)*R(&
&1,2)
tt13 = 1.0E+0*R(1,2)*C(2,6)+1.0E+0*R(1,3)*C(2,5)+1.0E+0*R(1,1)*C(&
&2,1)
tt14 = 1.0E+0*R(1,2)*C(4,6)+1.0E+0*R(1,3)*C(4,5)+1.0E+0*R(1,1)*C(&
&4,1)
tt15 = 1.0E+0*R(1,1)*C(5,6)+1.0E+0*R(1,3)*C(5,4)+1.0E+0*R(1,2)*C(&
&5,2)
tt16 = 1.0E+0*R(1,1)*C(6,6)+1.0E+0*R(1,3)*C(6,4)+1.0E+0*R(1,2)*C(&
&6,2)
tt17 = 5.0E-1*(1.0E+0*R(1,1)*tt3+1.0E+0*R(1,2)*tt16+1.0E+0*R(1,3)&
&*tt15+1.0E+0*R(1,3)*tt14+1.0E+0*R(1,2)*tt13+1.0E+0*R(1,1)*tt12)
tt18 = 1.0E+0*C(1,4)*R(2,3)+1.0E+0*C(1,2)*R(2,2)+1.0E+0*C(1,6)*R(&
&2,1)
tt19 = 1.0E+0*R(2,1)*C(5,6)+1.0E+0*R(2,3)*C(5,4)+1.0E+0*R(2,2)*C(&
&5,2)
tt20 = 1.0E+0*R(2,1)*C(6,6)+1.0E+0*R(2,3)*C(6,4)+1.0E+0*R(2,2)*C(&
&6,2)
tt21 = 5.0E-1*(1.0E+0*R(1,2)*tt20+1.0E+0*R(2,1)*tt3+1.0E+0*R(1,3)&
&*tt19+1.0E+0*R(2,3)*tt14+1.0E+0*R(2,2)*tt13+1.0E+0*R(1,1)*tt18)
tt22 = 1.0E+0*C(1,4)*R(3,3)+1.0E+0*C(1,2)*R(3,2)+1.0E+0*C(1,6)*R(&
&3,1)
tt23 = 1.0E+0*R(3,1)*C(5,6)+1.0E+0*R(3,3)*C(5,4)+1.0E+0*R(3,2)*C(&
&5,2)
tt24 = 1.0E+0*R(3,1)*C(6,6)+1.0E+0*R(3,3)*C(6,4)+1.0E+0*R(3,2)*C(&
&6,2)
tt25 = 5.0E-1*(1.0E+0*R(1,2)*tt24+1.0E+0*R(3,1)*tt3+1.0E+0*R(1,3)&
&*tt23+1.0E+0*R(3,3)*tt14+1.0E+0*R(1,1)*tt22+1.0E+0*tt13*R(3,2))
tt26 = 1.0E+0*R(1,1)*C(1,5)+1.0E+0*R(1,2)*C(1,4)+1.0E+0*C(1,3)*R(&
&1,3)
tt27 = 1.0E+0*R(1,2)*C(3,6)+1.0E+0*R(1,3)*C(3,5)+1.0E+0*R(1,1)*C(&
&3,1)
tt28 = 1.0E+0*R(1,1)*C(5,5)+1.0E+0*R(1,2)*C(5,4)+1.0E+0*R(1,3)*C(&
&5,3)
tt29 = 1.0E+0*R(1,1)*C(6,5)+1.0E+0*R(1,2)*C(6,4)+1.0E+0*R(1,3)*C(&
&6,3)
tt30 = 5.0E-1*(1.0E+0*R(1,2)*tt29+1.0E+0*R(1,1)*tt2+1.0E+0*R(1,3)&
&*tt28+1.0E+0*R(1,2)*tt14+1.0E+0*R(1,3)*tt27+1.0E+0*R(1,1)*tt26)
tt31 = 1.0E+0*C(1,3)*R(2,3)+1.0E+0*C(1,4)*R(2,2)+1.0E+0*C(1,5)*R(&
&2,1)
tt32 = 1.0E+0*R(2,1)*C(5,5)+1.0E+0*R(2,2)*C(5,4)+1.0E+0*R(2,3)*C(&
&5,3)
tt33 = 1.0E+0*R(2,1)*C(6,5)+1.0E+0*R(2,2)*C(6,4)+1.0E+0*R(2,3)*C(&
&6,3)
tt34 = 5.0E-1*(1.0E+0*R(1,2)*tt33+1.0E+0*R(2,1)*tt2+1.0E+0*R(1,3)&
&*tt32+1.0E+0*R(2,2)*tt14+1.0E+0*R(2,3)*tt27+1.0E+0*R(1,1)*tt31)
tt35 = 1.0E+0*C(1,3)*R(3,3)+1.0E+0*C(1,4)*R(3,2)+1.0E+0*C(1,5)*R(&
&3,1)
tt36 = 1.0E+0*R(3,1)*C(5,5)+1.0E+0*R(3,2)*C(5,4)+1.0E+0*R(3,3)*C(&
&5,3)
tt37 = 1.0E+0*R(3,1)*C(6,5)+1.0E+0*R(3,2)*C(6,4)+1.0E+0*R(3,3)*C(&
&6,3)
tt38 = 5.0E-1*(1.0E+0*R(1,2)*tt37+1.0E+0*R(3,1)*tt2+1.0E+0*R(1,3)&
&*tt36+1.0E+0*R(3,2)*tt14+1.0E+0*R(3,3)*tt27+1.0E+0*R(1,1)*tt35)
tt39 = 5.0E-1*(1.0E+0*R(2,2)*tt10+1.0E+0*R(3,2)*tt6+1.0E+0*R(2,3)&
&*tt9+1.0E+0*R(3,3)*tt5+1.0E+0*R(2,1)*tt8+1.0E+0*tt4*R(3,1))
tt40 = 1.0E+0*R(2,2)*C(2,6)+1.0E+0*R(2,3)*C(2,5)+1.0E+0*C(2,1)*R(&
&2,1)
tt41 = 1.0E+0*R(2,2)*C(4,6)+1.0E+0*R(2,3)*C(4,5)+1.0E+0*R(2,1)*C(&
&4,1)
tt42 = 5.0E-1*(1.0E+0*R(1,1)*tt6+1.0E+0*R(2,2)*tt16+1.0E+0*R(2,3)&
&*tt15+1.0E+0*R(1,3)*tt41+1.0E+0*R(1,2)*tt40+1.0E+0*tt12*R(2,1))
tt43 = 5.0E-1*(1.0E+0*R(2,1)*tt6+1.0E+0*R(2,2)*tt20+1.0E+0*R(2,3)&
&*tt19+1.0E+0*R(2,3)*tt41+1.0E+0*R(2,2)*tt40+1.0E+0*R(2,1)*tt18)
tt44 = 5.0E-1*(1.0E+0*R(2,2)*tt24+1.0E+0*R(3,1)*tt6+1.0E+0*R(2,3)&
&*tt23+1.0E+0*R(3,3)*tt41+1.0E+0*R(2,1)*tt22+1.0E+0*tt40*R(3,2))
tt45 = 1.0E+0*R(2,2)*C(3,6)+1.0E+0*R(2,3)*C(3,5)+1.0E+0*R(2,1)*C(&
&3,1)
tt46 = 5.0E-1*(1.0E+0*R(2,2)*tt29+1.0E+0*R(1,1)*tt5+1.0E+0*R(2,3)&
&*tt28+1.0E+0*R(1,2)*tt41+1.0E+0*R(1,3)*tt45+1.0E+0*tt26*R(2,1))
tt47 = 5.0E-1*(1.0E+0*R(2,2)*tt33+1.0E+0*R(2,1)*tt5+1.0E+0*R(2,3)&
&*tt32+1.0E+0*R(2,2)*tt41+1.0E+0*R(2,3)*tt45+1.0E+0*R(2,1)*tt31)
tt48 = 5.0E-1*(1.0E+0*R(2,2)*tt37+1.0E+0*R(3,1)*tt5+1.0E+0*R(2,3)&
&*tt36+1.0E+0*R(3,2)*tt41+1.0E+0*R(3,3)*tt45+1.0E+0*R(2,1)*tt35)
tt49 = 1.0E+0*C(2,5)*R(3,3)+1.0E+0*C(2,6)*R(3,2)+1.0E+0*C(2,1)*R(&
&3,1)
tt50 = 1.0E+0*R(3,2)*C(4,6)+1.0E+0*R(3,3)*C(4,5)+1.0E+0*R(3,1)*C(&
&4,1)
tt51 = 5.0E-1*(1.0E+0*R(1,1)*tt10+1.0E+0*R(3,2)*tt16+1.0E+0*R(3,3&
&)*tt15+1.0E+0*R(1,3)*tt50+1.0E+0*R(1,2)*tt49+1.0E+0*tt12*R(3,1))
tt52 = 5.0E-1*(1.0E+0*R(2,1)*tt10+1.0E+0*R(3,2)*tt20+1.0E+0*R(3,3&
&)*tt19+1.0E+0*R(2,3)*tt50+1.0E+0*R(2,2)*tt49+1.0E+0*tt18*R(3,1))
tt53 = 5.0E-1*(1.0E+0*R(3,1)*tt10+1.0E+0*R(3,2)*tt24+1.0E+0*R(3,3&
&)*tt23+1.0E+0*R(3,3)*tt50+1.0E+0*R(3,2)*tt49+1.0E+0*R(3,1)*tt22)
tt54 = 1.0E+0*R(3,2)*C(3,6)+1.0E+0*R(3,3)*C(3,5)+1.0E+0*C(3,1)*R(&
&3,1)
tt55 = 5.0E-1*(1.0E+0*R(3,2)*tt29+1.0E+0*R(1,1)*tt9+1.0E+0*R(3,3)&
&*tt28+1.0E+0*R(1,2)*tt50+1.0E+0*R(1,3)*tt54+1.0E+0*tt26*R(3,1))
tt56 = 5.0E-1*(1.0E+0*R(3,2)*tt33+1.0E+0*R(2,1)*tt9+1.0E+0*R(3,3)&
&*tt32+1.0E+0*R(2,2)*tt50+1.0E+0*R(2,3)*tt54+1.0E+0*tt31*R(3,1))
tt57 = 5.0E-1*(1.0E+0*R(3,2)*tt37+1.0E+0*R(3,1)*tt9+1.0E+0*R(3,3)&
&*tt36+1.0E+0*R(3,2)*tt50+1.0E+0*R(3,3)*tt54+1.0E+0*R(3,1)*tt35)
tt58 = 1.0E+0*R(1,1)*C(2,6)+1.0E+0*R(1,3)*C(2,4)+1.0E+0*R(1,2)*C(&
&2,2)
tt59 = 1.0E+0*R(1,1)*C(4,6)+1.0E+0*R(1,3)*C(4,4)+1.0E+0*R(1,2)*C(&
&4,2)
tt60 = 1.0E+0*R(2,1)*C(2,6)+1.0E+0*R(2,3)*C(2,4)+1.0E+0*C(2,2)*R(&
&2,2)
tt61 = 1.0E+0*R(2,1)*C(4,6)+1.0E+0*R(2,3)*C(4,4)+1.0E+0*R(2,2)*C(&
&4,2)
tt62 = 5.0E-1*(1.0E+0*R(1,1)*tt20+1.0E+0*R(2,1)*tt16+1.0E+0*R(1,3&
&)*tt61+1.0E+0*R(2,3)*tt59+1.0E+0*R(1,2)*tt60+1.0E+0*R(2,2)*tt58)
tt63 = 1.0E+0*C(2,4)*R(3,3)+1.0E+0*C(2,2)*R(3,2)+1.0E+0*C(2,6)*R(&
&3,1)
tt64 = 1.0E+0*R(3,1)*C(4,6)+1.0E+0*R(3,3)*C(4,4)+1.0E+0*R(3,2)*C(&
&4,2)
tt65 = 5.0E-1*(1.0E+0*R(1,1)*tt24+1.0E+0*R(3,1)*tt16+1.0E+0*R(1,3&
&)*tt64+1.0E+0*R(3,3)*tt59+1.0E+0*R(1,2)*tt63+1.0E+0*tt58*R(3,2))
tt66 = 1.0E+0*R(1,1)*C(2,5)+1.0E+0*R(1,2)*C(2,4)+1.0E+0*R(1,3)*C(&
&2,3)
tt67 = 1.0E+0*R(1,1)*C(3,6)+1.0E+0*R(1,3)*C(3,4)+1.0E+0*R(1,2)*C(&
&3,2)
tt68 = 1.0E+0*R(1,1)*C(4,5)+1.0E+0*R(1,2)*C(4,4)+1.0E+0*R(1,3)*C(&
&4,3)
tt69 = 5.0E-1*(1.0E+0*R(1,1)*tt29+1.0E+0*R(1,1)*tt15+1.0E+0*R(1,2&
&)*tt59+1.0E+0*R(1,3)*tt68+1.0E+0*R(1,3)*tt67+1.0E+0*R(1,2)*tt66)
tt70 = 1.0E+0*R(2,1)*C(2,5)+1.0E+0*R(2,2)*C(2,4)+1.0E+0*C(2,3)*R(&
&2,3)
tt71 = 1.0E+0*R(2,1)*C(4,5)+1.0E+0*R(2,2)*C(4,4)+1.0E+0*R(2,3)*C(&
&4,3)
tt72 = 5.0E-1*(1.0E+0*R(1,1)*tt33+1.0E+0*R(2,1)*tt15+1.0E+0*R(2,2&
&)*tt59+1.0E+0*R(1,3)*tt71+1.0E+0*R(2,3)*tt67+1.0E+0*R(1,2)*tt70)
tt73 = 1.0E+0*C(2,3)*R(3,3)+1.0E+0*C(2,4)*R(3,2)+1.0E+0*C(2,5)*R(&
&3,1)
tt74 = 1.0E+0*R(3,1)*C(4,5)+1.0E+0*R(3,2)*C(4,4)+1.0E+0*R(3,3)*C(&
&4,3)
tt75 = 5.0E-1*(1.0E+0*R(1,1)*tt37+1.0E+0*R(3,1)*tt15+1.0E+0*R(3,2&
&)*tt59+1.0E+0*R(1,3)*tt74+1.0E+0*R(3,3)*tt67+1.0E+0*R(1,2)*tt73)
tt76 = 5.0E-1*(1.0E+0*R(2,1)*tt24+1.0E+0*R(3,1)*tt20+1.0E+0*R(2,3&
&)*tt64+1.0E+0*R(3,3)*tt61+1.0E+0*R(2,2)*tt63+1.0E+0*tt60*R(3,2))
tt77 = 1.0E+0*R(2,1)*C(3,6)+1.0E+0*R(2,3)*C(3,4)+1.0E+0*R(2,2)*C(&
&3,2)
tt78 = 5.0E-1*(1.0E+0*R(2,1)*tt29+1.0E+0*R(1,1)*tt19+1.0E+0*R(1,2&
&)*tt61+1.0E+0*R(2,3)*tt68+1.0E+0*R(1,3)*tt77+1.0E+0*R(2,2)*tt66)
tt79 = 5.0E-1*(1.0E+0*R(2,1)*tt33+1.0E+0*R(2,1)*tt19+1.0E+0*R(2,2&
&)*tt61+1.0E+0*R(2,3)*tt71+1.0E+0*R(2,3)*tt77+1.0E+0*R(2,2)*tt70)
tt80 = 5.0E-1*(1.0E+0*R(2,1)*tt37+1.0E+0*R(3,1)*tt19+1.0E+0*R(3,2&
&)*tt61+1.0E+0*R(2,3)*tt74+1.0E+0*R(3,3)*tt77+1.0E+0*R(2,2)*tt73)
tt81 = 1.0E+0*R(3,1)*C(3,6)+1.0E+0*R(3,3)*C(3,4)+1.0E+0*C(3,2)*R(&
&3,2)
tt82 = 5.0E-1*(1.0E+0*R(3,1)*tt29+1.0E+0*R(1,1)*tt23+1.0E+0*R(1,2&
&)*tt64+1.0E+0*R(3,3)*tt68+1.0E+0*R(1,3)*tt81+1.0E+0*tt66*R(3,2))
tt83 = 5.0E-1*(1.0E+0*R(3,1)*tt33+1.0E+0*R(2,1)*tt23+1.0E+0*R(2,2&
&)*tt64+1.0E+0*R(3,3)*tt71+1.0E+0*R(2,3)*tt81+1.0E+0*tt70*R(3,2))
tt84 = 5.0E-1*(1.0E+0*R(3,1)*tt37+1.0E+0*R(3,1)*tt23+1.0E+0*R(3,2&
&)*tt64+1.0E+0*R(3,3)*tt74+1.0E+0*R(3,3)*tt81+1.0E+0*R(3,2)*tt73)
tt85 = 1.0E+0*R(1,1)*C(3,5)+1.0E+0*R(1,2)*C(3,4)+1.0E+0*R(1,3)*C(&
&3,3)
tt86 = 1.0E+0*R(2,1)*C(3,5)+1.0E+0*R(2,2)*C(3,4)+1.0E+0*R(2,3)*C(&
&3,3)
tt87 = 5.0E-1*(1.0E+0*R(1,1)*tt32+1.0E+0*R(2,1)*tt28+1.0E+0*R(1,2&
&)*tt71+1.0E+0*R(2,2)*tt68+1.0E+0*R(1,3)*tt86+1.0E+0*R(2,3)*tt85)
tt88 = 1.0E+0*R(3,1)*C(3,5)+1.0E+0*R(3,2)*C(3,4)+1.0E+0*C(3,3)*R(&
&3,3)
tt89 = 5.0E-1*(1.0E+0*R(1,1)*tt36+1.0E+0*R(3,1)*tt28+1.0E+0*R(1,2&
&)*tt74+1.0E+0*R(3,2)*tt68+1.0E+0*R(1,3)*tt88+1.0E+0*R(3,3)*tt85)
tt90 = 5.0E-1*(1.0E+0*R(2,1)*tt36+1.0E+0*R(3,1)*tt32+1.0E+0*R(2,2&
&)*tt74+1.0E+0*R(3,2)*tt71+1.0E+0*R(2,3)*tt88+1.0E+0*R(3,3)*tt86)
hes(1,1) = 5.0E-1*(2.0E+0*R(1,2)*tt3+2.0E+0*R(1,3)*tt2+2.0E+0*R(1&
&,1)*tt1)
hes(1,2) = tt7
hes(1,3) = tt11
hes(1,4) = tt17
hes(1,5) = tt21
hes(1,6) = tt25
hes(1,7) = tt30
hes(1,8) = tt34
hes(1,9) = tt38
hes(2,1) = tt7
hes(2,2) = 5.0E-1*(2.0E+0*R(2,2)*tt6+2.0E+0*R(2,3)*tt5+2.0E+0*R(2&
&,1)*tt4)
hes(2,3) = tt39
hes(2,4) = tt42
hes(2,5) = tt43
hes(2,6) = tt44
hes(2,7) = tt46
hes(2,8) = tt47
hes(2,9) = tt48
hes(3,1) = tt11
hes(3,2) = tt39
hes(3,3) = 5.0E-1*(2.0E+0*R(3,2)*tt10+2.0E+0*R(3,3)*tt9+2.0E+0*R(&
&3,1)*tt8)
hes(3,4) = tt51
hes(3,5) = tt52
hes(3,6) = tt53
hes(3,7) = tt55
hes(3,8) = tt56
hes(3,9) = tt57
hes(4,1) = tt17
hes(4,2) = tt42
hes(4,3) = tt51
hes(4,4) = 5.0E-1*(2.0E+0*R(1,1)*tt16+2.0E+0*R(1,3)*tt59+2.0E+0*R&
&(1,2)*tt58)
hes(4,5) = tt62
hes(4,6) = tt65
hes(4,7) = tt69
hes(4,8) = tt72
hes(4,9) = tt75
hes(5,1) = tt21
hes(5,2) = tt43
hes(5,3) = tt52
hes(5,4) = tt62
hes(5,5) = 5.0E-1*(2.0E+0*R(2,1)*tt20+2.0E+0*R(2,3)*tt61+2.0E+0*R&
&(2,2)*tt60)
hes(5,6) = tt76
hes(5,7) = tt78
hes(5,8) = tt79
hes(5,9) = tt80
hes(6,1) = tt25
hes(6,2) = tt44
hes(6,3) = tt53
hes(6,4) = tt65
hes(6,5) = tt76
hes(6,6) = 5.0E-1*(2.0E+0*R(3,1)*tt24+2.0E+0*R(3,3)*tt64+2.0E+0*R&
&(3,2)*tt63)
hes(6,7) = tt82
hes(6,8) = tt83
hes(6,9) = tt84
hes(7,1) = tt30
hes(7,2) = tt46
hes(7,3) = tt55
hes(7,4) = tt69
hes(7,5) = tt78
hes(7,6) = tt82
hes(7,7) = 5.0E-1*(2.0E+0*R(1,1)*tt28+2.0E+0*R(1,2)*tt68+2.0E+0*R&
&(1,3)*tt85)
hes(7,8) = tt87
hes(7,9) = tt89
hes(8,1) = tt34
hes(8,2) = tt47
hes(8,3) = tt56
hes(8,4) = tt72
hes(8,5) = tt79
hes(8,6) = tt83
hes(8,7) = tt87
hes(8,8) = 5.0E-1*(2.0E+0*R(2,1)*tt32+2.0E+0*R(2,2)*tt71+2.0E+0*R&
&(2,3)*tt86)
hes(8,9) = tt90
hes(9,1) = tt38
hes(9,2) = tt48
hes(9,3) = tt57
hes(9,4) = tt75
hes(9,5) = tt80
hes(9,6) = tt84
hes(9,7) = tt89
hes(9,8) = tt90
hes(9,9) = 5.0E-1*(2.0E+0*R(3,1)*tt36+2.0E+0*R(3,2)*tt74+2.0E+0*R&
&(3,3)*tt88)
END
SUBROUTINE &
&I_C_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = F(3,3)**2+F(3,2)**2+F(3,1)**2+F(2,3)**2+F(2,2)**2+F(2,&
&1)**2+F(1,3)**2+F(1,2)**2+F(1,1)**2
END
SUBROUTINE &
&I_C_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
jac(1,1) = 2*F(1,1)
jac(1,2) = 2*F(2,1)
jac(1,3) = 2*F(3,1)
jac(1,4) = 2*F(1,2)
jac(1,5) = 2*F(2,2)
jac(1,6) = 2*F(3,2)
jac(1,7) = 2*F(1,3)
jac(1,8) = 2*F(2,3)
jac(1,9) = 2*F(3,3)
END
SUBROUTINE &
&I_C_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
hes(1,1) = 2
hes(1,2) = 0
hes(1,3) = 0
hes(1,4) = 0
hes(1,5) = 0
hes(1,6) = 0
hes(1,7) = 0
hes(1,8) = 0
hes(1,9) = 0
hes(2,1) = 0
hes(2,2) = 2
hes(2,3) = 0
hes(2,4) = 0
hes(2,5) = 0
hes(2,6) = 0
hes(2,7) = 0
hes(2,8) = 0
hes(2,9) = 0
hes(3,1) = 0
hes(3,2) = 0
hes(3,3) = 2
hes(3,4) = 0
hes(3,5) = 0
hes(3,6) = 0
hes(3,7) = 0
hes(3,8) = 0
hes(3,9) = 0
hes(4,1) = 0
hes(4,2) = 0
hes(4,3) = 0
hes(4,4) = 2
hes(4,5) = 0
hes(4,6) = 0
hes(4,7) = 0
hes(4,8) = 0
hes(4,9) = 0
hes(5,1) = 0
hes(5,2) = 0
hes(5,3) = 0
hes(5,4) = 0
hes(5,5) = 2
hes(5,6) = 0
hes(5,7) = 0
hes(5,8) = 0
hes(5,9) = 0
hes(6,1) = 0
hes(6,2) = 0
hes(6,3) = 0
hes(6,4) = 0
hes(6,5) = 0
hes(6,6) = 2
hes(6,7) = 0
hes(6,8) = 0
hes(6,9) = 0
hes(7,1) = 0
hes(7,2) = 0
hes(7,3) = 0
hes(7,4) = 0
hes(7,5) = 0
hes(7,6) = 0
hes(7,7) = 2
hes(7,8) = 0
hes(7,9) = 0
hes(8,1) = 0
hes(8,2) = 0
hes(8,3) = 0
hes(8,4) = 0
hes(8,5) = 0
hes(8,6) = 0
hes(8,7) = 0
hes(8,8) = 2
hes(8,9) = 0
hes(9,1) = 0
hes(9,2) = 0
hes(9,3) = 0
hes(9,4) = 0
hes(9,5) = 0
hes(9,6) = 0
hes(9,7) = 0
hes(9,8) = 0
hes(9,9) = 2
END
SUBROUTINE &
&II_C_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
val(1,1) = (F(3,3)**2+F(2,3)**2+F(1,3)**2)**2+2*(F(3,2)*F(3,3)+F(&
&2,2)*F(2,3)+F(1,2)*F(1,3))**2+2*(F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,&
&1)*F(1,3))**2+(F(3,2)**2+F(2,2)**2+F(1,2)**2)**2+2*(F(3,1)*F(3,2)&
&+F(2,1)*F(2,2)+F(1,1)*F(1,2))**2+(F(3,1)**2+F(2,1)**2+F(1,1)**2)*&
&*2
END
SUBROUTINE &
&II_C_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
tt1 = F(3,1)**2+F(2,1)**2+F(1,1)**2
tt2 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt3 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt4 = F(3,2)**2+F(2,2)**2+F(1,2)**2
tt5 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt6 = F(3,3)**2+F(2,3)**2+F(1,3)**2
jac(1,1) = 4*F(1,3)*tt3+4*F(1,2)*tt2+4*F(1,1)*tt1
jac(1,2) = 4*F(2,3)*tt3+4*F(2,2)*tt2+4*F(2,1)*tt1
jac(1,3) = 4*F(3,3)*tt3+4*F(3,2)*tt2+4*F(3,1)*tt1
jac(1,4) = 4*F(1,3)*tt5+4*F(1,2)*tt4+4*F(1,1)*tt2
jac(1,5) = 4*F(2,3)*tt5+4*F(2,2)*tt4+4*F(2,1)*tt2
jac(1,6) = 4*F(3,3)*tt5+4*F(3,2)*tt4+4*F(3,1)*tt2
jac(1,7) = 4*F(1,3)*tt6+4*F(1,2)*tt5+4*F(1,1)*tt3
jac(1,8) = 4*F(2,3)*tt6+4*F(2,2)*tt5+4*F(2,1)*tt3
jac(1,9) = 4*F(3,3)*tt6+4*F(3,2)*tt5+4*F(3,1)*tt3
END
SUBROUTINE &
&II_C_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
REAL(KIND=8)  tt64
REAL(KIND=8)  tt65
REAL(KIND=8)  tt66
REAL(KIND=8)  tt67
REAL(KIND=8)  tt68
REAL(KIND=8)  tt69
tt1 = F(1,1)**2
tt2 = F(1,2)**2
tt3 = 4*tt2
tt4 = F(1,3)**2
tt5 = 4*tt4
tt6 = F(2,1)**2
tt7 = F(3,1)**2
tt8 = 4*(tt7+tt6+tt1)
tt9 = 4*F(1,2)*F(2,2)
tt10 = 4*F(1,3)*F(2,3)
tt11 = tt10+tt9+8*F(1,1)*F(2,1)
tt12 = 4*F(1,2)*F(3,2)
tt13 = 4*F(1,3)*F(3,3)
tt14 = tt13+tt12+8*F(1,1)*F(3,1)
tt15 = 4*(F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2))
tt16 = tt15+4*F(1,1)*F(1,2)
tt17 = 4*F(1,2)*F(2,1)
tt18 = 4*F(1,2)*F(3,1)
tt19 = 4*(F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3))
tt20 = tt19+4*F(1,1)*F(1,3)
tt21 = 4*F(1,3)*F(2,1)
tt22 = 4*F(1,3)*F(3,1)
tt23 = F(2,2)**2
tt24 = 4*tt23
tt25 = F(2,3)**2
tt26 = 4*tt25
tt27 = 4*F(2,2)*F(3,2)
tt28 = 4*F(2,3)*F(3,3)
tt29 = tt28+tt27+8*F(2,1)*F(3,1)
tt30 = 4*F(1,1)*F(2,2)
tt31 = tt15+4*F(2,1)*F(2,2)
tt32 = 4*F(2,2)*F(3,1)
tt33 = 4*F(1,1)*F(2,3)
tt34 = tt19+4*F(2,1)*F(2,3)
tt35 = 4*F(2,3)*F(3,1)
tt36 = F(3,2)**2
tt37 = 4*tt36
tt38 = F(3,3)**2
tt39 = 4*tt38
tt40 = 4*F(1,1)*F(3,2)
tt41 = 4*F(2,1)*F(3,2)
tt42 = tt15+4*F(3,1)*F(3,2)
tt43 = 4*F(1,1)*F(3,3)
tt44 = 4*F(2,1)*F(3,3)
tt45 = tt19+4*F(3,1)*F(3,3)
tt46 = 4*tt1
tt47 = 4*(tt36+tt23+tt2)
tt48 = 4*F(1,1)*F(2,1)
tt49 = tt10+8*F(1,2)*F(2,2)+tt48
tt50 = 4*F(1,1)*F(3,1)
tt51 = tt13+8*F(1,2)*F(3,2)+tt50
tt52 = 4*(F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3))
tt53 = tt52+4*F(1,2)*F(1,3)
tt54 = 4*F(1,3)*F(2,2)
tt55 = 4*F(1,3)*F(3,2)
tt56 = 4*tt6
tt57 = 4*F(2,1)*F(3,1)
tt58 = tt28+8*F(2,2)*F(3,2)+tt57
tt59 = 4*F(1,2)*F(2,3)
tt60 = tt52+4*F(2,2)*F(2,3)
tt61 = 4*F(2,3)*F(3,2)
tt62 = 4*tt7
tt63 = 4*F(1,2)*F(3,3)
tt64 = 4*F(2,2)*F(3,3)
tt65 = tt52+4*F(3,2)*F(3,3)
tt66 = 4*(tt38+tt25+tt4)
tt67 = 8*F(1,3)*F(2,3)+tt9+tt48
tt68 = 8*F(1,3)*F(3,3)+tt12+tt50
tt69 = 8*F(2,3)*F(3,3)+tt27+tt57
hes(1,1) = tt8+tt5+tt3+8*tt1
hes(1,2) = tt11
hes(1,3) = tt14
hes(1,4) = tt16
hes(1,5) = tt17
hes(1,6) = tt18
hes(1,7) = tt20
hes(1,8) = tt21
hes(1,9) = tt22
hes(2,1) = tt11
hes(2,2) = tt8+tt26+tt24+8*tt6
hes(2,3) = tt29
hes(2,4) = tt30
hes(2,5) = tt31
hes(2,6) = tt32
hes(2,7) = tt33
hes(2,8) = tt34
hes(2,9) = tt35
hes(3,1) = tt14
hes(3,2) = tt29
hes(3,3) = tt39+tt37+tt8+8*tt7
hes(3,4) = tt40
hes(3,5) = tt41
hes(3,6) = tt42
hes(3,7) = tt43
hes(3,8) = tt44
hes(3,9) = tt45
hes(4,1) = tt16
hes(4,2) = tt30
hes(4,3) = tt40
hes(4,4) = tt47+tt5+8*tt2+tt46
hes(4,5) = tt49
hes(4,6) = tt51
hes(4,7) = tt53
hes(4,8) = tt54
hes(4,9) = tt55
hes(5,1) = tt17
hes(5,2) = tt31
hes(5,3) = tt41
hes(5,4) = tt49
hes(5,5) = tt47+tt26+8*tt23+tt56
hes(5,6) = tt58
hes(5,7) = tt59
hes(5,8) = tt60
hes(5,9) = tt61
hes(6,1) = tt18
hes(6,2) = tt32
hes(6,3) = tt42
hes(6,4) = tt51
hes(6,5) = tt58
hes(6,6) = tt39+tt47+8*tt36+tt62
hes(6,7) = tt63
hes(6,8) = tt64
hes(6,9) = tt65
hes(7,1) = tt20
hes(7,2) = tt33
hes(7,3) = tt43
hes(7,4) = tt53
hes(7,5) = tt59
hes(7,6) = tt63
hes(7,7) = tt66+8*tt4+tt3+tt46
hes(7,8) = tt67
hes(7,9) = tt68
hes(8,1) = tt21
hes(8,2) = tt34
hes(8,3) = tt44
hes(8,4) = tt54
hes(8,5) = tt60
hes(8,6) = tt64
hes(8,7) = tt67
hes(8,8) = tt66+8*tt25+tt24+tt56
hes(8,9) = tt69
hes(9,1) = tt22
hes(9,2) = tt35
hes(9,3) = tt45
hes(9,4) = tt55
hes(9,5) = tt61
hes(9,6) = tt65
hes(9,7) = tt68
hes(9,8) = tt69
hes(9,9) = tt66+8*tt38+tt37+tt62
END
SUBROUTINE &
&III_C_3d_val(&
&  val &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) val(1, 1)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
tt1 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt2 = F(3,2)**2+F(2,2)**2+F(1,2)**2
tt3 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt4 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt5 = F(3,3)**2+F(2,3)**2+F(1,3)**2
val(1,1) = (F(3,1)**2+F(2,1)**2+F(1,1)**2)*(tt2*tt5-tt4**2)-tt3*(&
&tt3*tt5-tt1*tt4)+tt1*(tt3*tt4-tt2*tt1)
END
SUBROUTINE &
&III_C_3d_jac(&
&  jac &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) jac(1, 9)
REAL(KIND=8) F(3, 3)
REAL(KIND=8)  tt1
REAL(KIND=8)  tt2
REAL(KIND=8)  tt3
REAL(KIND=8)  tt4
REAL(KIND=8)  tt5
REAL(KIND=8)  tt6
REAL(KIND=8)  tt7
REAL(KIND=8)  tt8
REAL(KIND=8)  tt9
tt1 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt2 = F(3,2)**2+F(2,2)**2+F(1,2)**2
tt3 = F(3,2)*F(3,3)+F(2,2)*F(2,3)+F(1,2)*F(1,3)
tt4 = F(3,1)*F(3,2)+F(2,1)*F(2,2)+F(1,1)*F(1,2)
tt5 = tt4*tt3-tt2*tt1
tt6 = F(3,3)**2+F(2,3)**2+F(1,3)**2
tt7 = tt4*tt6-tt1*tt3
tt8 = tt2*tt6-tt3**2
tt9 = F(3,1)**2+F(2,1)**2+F(1,1)**2
jac(1,1) = 2*F(1,1)*tt8-F(1,2)*tt7-tt4*(F(1,2)*tt6-F(1,3)*tt3)+F(&
&1,3)*tt5+tt1*(F(1,2)*tt3-F(1,3)*tt2)
jac(1,2) = 2*F(2,1)*tt8-F(2,2)*tt7-tt4*(F(2,2)*tt6-F(2,3)*tt3)+F(&
&2,3)*tt5+tt1*(F(2,2)*tt3-F(2,3)*tt2)
jac(1,3) = 2*F(3,1)*tt8-F(3,2)*tt7-tt4*(F(3,2)*tt6-F(3,3)*tt3)+F(&
&3,3)*tt5+tt1*(F(3,2)*tt3-tt2*F(3,3))
jac(1,4) = (-F(1,1)*tt7)+tt9*(2*F(1,2)*tt6-2*F(1,3)*tt3)-tt4*(F(1&
&,1)*tt6-F(1,3)*tt1)+tt1*(F(1,1)*tt3-2*F(1,2)*tt1+F(1,3)*tt4)
jac(1,5) = (-F(2,1)*tt7)+tt9*(2*F(2,2)*tt6-2*F(2,3)*tt3)-tt4*(F(2&
&,1)*tt6-F(2,3)*tt1)+tt1*(F(2,1)*tt3-2*F(2,2)*tt1+F(2,3)*tt4)
jac(1,6) = (-F(3,1)*tt7)+tt9*(2*F(3,2)*tt6-2*F(3,3)*tt3)-tt4*(F(3&
&,1)*tt6-F(3,3)*tt1)+tt1*(F(3,1)*tt3-2*F(3,2)*tt1+tt4*F(3,3))
jac(1,7) = F(1,1)*tt5+tt9*(2*F(1,3)*tt2-2*F(1,2)*tt3)-tt4*((-F(1,&
&1)*tt3)-F(1,2)*tt1+2*F(1,3)*tt4)+(F(1,2)*tt4-F(1,1)*tt2)*tt1
jac(1,8) = F(2,1)*tt5+tt9*(2*F(2,3)*tt2-2*F(2,2)*tt3)-tt4*((-F(2,&
&1)*tt3)-F(2,2)*tt1+2*F(2,3)*tt4)+(F(2,2)*tt4-F(2,1)*tt2)*tt1
jac(1,9) = F(3,1)*tt5+tt9*(2*tt2*F(3,3)-2*F(3,2)*tt3)-tt4*((-F(3,&
&1)*tt3)-F(3,2)*tt1+2*tt4*F(3,3))+(F(3,2)*tt4-F(3,1)*tt2)*tt1
END
SUBROUTINE &
&III_C_3d_hes(&
&  hes &
&, F &
&)
IMPLICIT NONE
REAL(KIND=8) hes(9, 9)
REAL(KIND=8) F(3, 3)
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
REAL(KIND=8)  tt27
REAL(KIND=8)  tt28
REAL(KIND=8)  tt29
REAL(KIND=8)  tt30
REAL(KIND=8)  tt31
REAL(KIND=8)  tt32
REAL(KIND=8)  tt33
REAL(KIND=8)  tt34
REAL(KIND=8)  tt35
REAL(KIND=8)  tt36
REAL(KIND=8)  tt37
REAL(KIND=8)  tt38
REAL(KIND=8)  tt39
REAL(KIND=8)  tt40
REAL(KIND=8)  tt41
REAL(KIND=8)  tt42
REAL(KIND=8)  tt43
REAL(KIND=8)  tt44
REAL(KIND=8)  tt45
REAL(KIND=8)  tt46
REAL(KIND=8)  tt47
REAL(KIND=8)  tt48
REAL(KIND=8)  tt49
REAL(KIND=8)  tt50
REAL(KIND=8)  tt51
REAL(KIND=8)  tt52
REAL(KIND=8)  tt53
REAL(KIND=8)  tt54
REAL(KIND=8)  tt55
REAL(KIND=8)  tt56
REAL(KIND=8)  tt57
REAL(KIND=8)  tt58
REAL(KIND=8)  tt59
REAL(KIND=8)  tt60
REAL(KIND=8)  tt61
REAL(KIND=8)  tt62
REAL(KIND=8)  tt63
REAL(KIND=8)  tt64
REAL(KIND=8)  tt65
REAL(KIND=8)  tt66
REAL(KIND=8)  tt67
REAL(KIND=8)  tt68
REAL(KIND=8)  tt69
REAL(KIND=8)  tt70
REAL(KIND=8)  tt71
REAL(KIND=8)  tt72
REAL(KIND=8)  tt73
REAL(KIND=8)  tt74
REAL(KIND=8)  tt75
REAL(KIND=8)  tt76
REAL(KIND=8)  tt77
REAL(KIND=8)  tt78
REAL(KIND=8)  tt79
REAL(KIND=8)  tt80
REAL(KIND=8)  tt81
REAL(KIND=8)  tt82
REAL(KIND=8)  tt83
REAL(KIND=8)  tt84
REAL(KIND=8)  tt85
REAL(KIND=8)  tt86
REAL(KIND=8)  tt87
REAL(KIND=8)  tt88
REAL(KIND=8)  tt89
REAL(KIND=8)  tt90
REAL(KIND=8)  tt91
REAL(KIND=8)  tt92
REAL(KIND=8)  tt93
REAL(KIND=8)  tt94
REAL(KIND=8)  tt95
REAL(KIND=8)  tt96
REAL(KIND=8)  tt97
REAL(KIND=8)  tt98
REAL(KIND=8)  tt99
REAL(KIND=8)  tt100
REAL(KIND=8)  tt101
REAL(KIND=8)  tt102
REAL(KIND=8)  tt103
REAL(KIND=8)  tt104
REAL(KIND=8)  tt105
REAL(KIND=8)  tt106
REAL(KIND=8)  tt107
REAL(KIND=8)  tt108
REAL(KIND=8)  tt109
tt1 = F(1,2)**2
tt2 = F(2,2)**2
tt3 = F(3,2)**2
tt4 = tt3+tt2+tt1
tt5 = F(1,2)*F(1,3)
tt6 = F(2,2)*F(2,3)
tt7 = F(3,2)*F(3,3)
tt8 = tt7+tt6+tt5
tt9 = F(1,2)*tt8-F(1,3)*tt4
tt10 = F(1,3)**2
tt11 = F(2,3)**2
tt12 = F(3,3)**2
tt13 = tt12+tt11+tt10
tt14 = F(1,2)*tt13-F(1,3)*tt8
tt15 = 2*(tt4*tt13-tt8**2)
tt16 = F(2,2)*tt8-F(2,3)*tt4
tt17 = F(2,2)*tt13-F(2,3)*tt8
tt18 = (-F(1,2)*tt17)-F(2,2)*tt14+F(1,3)*tt16+F(2,3)*tt9
tt19 = F(3,2)*tt8-tt4*F(3,3)
tt20 = F(3,2)*tt13-F(3,3)*tt8
tt21 = (-F(1,2)*tt20)-F(3,2)*tt14+F(1,3)*tt19+F(3,3)*tt9
tt22 = F(3,1)*F(3,3)+F(2,1)*F(2,3)+F(1,1)*F(1,3)
tt23 = tt22*tt8
tt24 = F(1,1)*F(1,2)
tt25 = F(2,1)*F(2,2)
tt26 = F(3,1)*F(3,2)
tt27 = tt26+tt25+tt24
tt28 = F(1,1)*tt8-2*F(1,2)*tt22+F(1,3)*tt27
tt29 = -tt27*tt13
tt30 = F(1,1)*tt13-F(1,3)*tt22
tt31 = 2*F(1,2)*tt13-2*F(1,3)*tt8
tt32 = 2*F(1,1)*tt31-F(1,1)*tt14-F(1,2)*tt30+tt29-tt27*(tt12+tt11&
&)+F(1,3)*tt28+tt23+tt22*(tt7+tt6)
tt33 = F(1,3)*F(2,3)*tt27
tt34 = -2*F(1,3)*F(2,2)
tt35 = F(2,1)*tt8-2*F(2,2)*tt22+F(2,3)*tt27
tt36 = F(2,1)*tt13-F(2,3)*tt22
tt37 = 2*F(2,2)*tt13-2*F(2,3)*tt8
tt38 = 2*F(1,1)*tt37-F(1,2)*tt36-F(2,1)*tt14+F(1,3)*tt35+(F(1,2)*&
&F(2,3)+tt34)*tt22+tt33
tt39 = F(1,3)*tt27*F(3,3)
tt40 = -2*F(1,3)*F(3,2)
tt41 = F(3,1)*tt8-2*F(3,2)*tt22+tt27*F(3,3)
tt42 = F(3,1)*tt13-F(3,3)*tt22
tt43 = 2*F(3,2)*tt13-2*F(3,3)*tt8
tt44 = 2*F(1,1)*tt43-F(1,2)*tt42-F(3,1)*tt14+F(1,3)*tt41+(F(1,2)*&
&F(3,3)+tt40)*tt22+tt39
tt45 = F(1,2)*tt27-F(1,1)*tt4
tt46 = -tt2
tt47 = -tt3
tt48 = -tt4*tt22
tt49 = -F(2,2)*F(2,3)
tt50 = -F(3,2)*F(3,3)
tt51 = tt27*tt8
tt52 = (-F(1,1)*tt8)-F(1,2)*tt22+2*F(1,3)*tt27
tt53 = 2*F(1,3)*tt4-2*F(1,2)*tt8
tt54 = F(1,1)*tt9+2*F(1,1)*tt53-F(1,2)*tt52+tt51-tt27*(tt50+tt49)&
&+tt48+(tt47+tt46)*tt22+F(1,3)*tt45
tt55 = F(2,2)*tt27-F(2,1)*tt4
tt56 = F(1,2)*F(2,2)*tt22
tt57 = (-F(2,1)*tt8)-F(2,2)*tt22+2*F(2,3)*tt27
tt58 = 2*F(2,3)*tt4-2*F(2,2)*tt8
tt59 = 2*F(1,1)*tt58-F(1,2)*tt57+F(2,1)*tt9+tt56+F(1,3)*tt55-(2*F&
&(1,2)*F(2,3)-F(1,3)*F(2,2))*tt27
tt60 = F(3,2)*tt27-F(3,1)*tt4
tt61 = F(1,2)*F(3,2)*tt22
tt62 = (-F(3,1)*tt8)-F(3,2)*tt22+2*tt27*F(3,3)
tt63 = 2*tt4*F(3,3)-2*F(3,2)*tt8
tt64 = 2*F(1,1)*tt63-F(1,2)*tt62+F(3,1)*tt9+tt61-tt27*(2*F(1,2)*F&
&(3,3)-F(1,3)*F(3,2))+F(1,3)*tt60
tt65 = (-F(2,2)*tt20)-F(3,2)*tt17+F(2,3)*tt19+F(3,3)*tt16
tt66 = -2*F(1,2)*F(2,3)
tt67 = (-F(1,1)*tt17)+2*F(2,1)*tt31-F(2,2)*tt30+F(2,3)*tt28+(tt66&
&+F(1,3)*F(2,2))*tt22+tt33
tt68 = 2*F(2,1)*tt37-F(2,1)*tt17-F(2,2)*tt36+tt29-tt27*(tt12+tt10&
&)+F(2,3)*tt35+tt23+tt22*(tt7+tt5)
tt69 = F(2,3)*tt27*F(3,3)
tt70 = -2*F(2,3)*F(3,2)
tt71 = 2*F(2,1)*tt43-F(2,2)*tt42-F(3,1)*tt17+F(2,3)*tt41+(F(2,2)*&
&F(3,3)+tt70)*tt22+tt69
tt72 = F(1,1)*tt16+2*F(2,1)*tt53-F(2,2)*tt52+tt56+F(2,3)*tt45-(2*&
&F(1,3)*F(2,2)-F(1,2)*F(2,3))*tt27
tt73 = -tt1
tt74 = -F(1,2)*F(1,3)
tt75 = F(2,1)*tt16+2*F(2,1)*tt58-F(2,2)*tt57+tt51-tt27*(tt50+tt74&
&)+tt48+(tt47+tt73)*tt22+F(2,3)*tt55
tt76 = F(2,2)*F(3,2)*tt22
tt77 = 2*F(2,1)*tt63-F(2,2)*tt62+F(3,1)*tt16+tt76-tt27*(2*F(2,2)*&
&F(3,3)-F(2,3)*F(3,2))+F(2,3)*tt60
tt78 = -2*F(1,2)*F(3,3)
tt79 = (-F(1,1)*tt20)+2*F(3,1)*tt31-F(3,2)*tt30+F(3,3)*tt28+(tt78&
&+F(1,3)*F(3,2))*tt22+tt39
tt80 = -2*F(2,2)*F(3,3)
tt81 = (-F(2,1)*tt20)+2*F(3,1)*tt37-F(3,2)*tt36+F(3,3)*tt35+(tt80&
&+F(2,3)*F(3,2))*tt22+tt69
tt82 = 2*F(3,1)*tt43-F(3,1)*tt20-F(3,2)*tt42+tt29+F(3,3)*tt41+tt2&
&3+(tt6+tt5)*tt22-(tt11+tt10)*tt27
tt83 = F(1,1)*tt19+2*F(3,1)*tt53-F(3,2)*tt52+tt61-tt27*(2*F(1,3)*&
&F(3,2)-F(1,2)*F(3,3))+tt45*F(3,3)
tt84 = F(2,1)*tt19+2*F(3,1)*tt58-F(3,2)*tt57+tt76-tt27*(2*F(2,3)*&
&F(3,2)-F(2,2)*F(3,3))+tt55*F(3,3)
tt85 = F(3,1)*tt19+2*F(3,1)*tt63-F(3,2)*tt62+tt51+tt48+(tt46+tt73&
&)*tt22+tt60*F(3,3)-(tt49+tt74)*tt27
tt86 = -2*tt22
tt87 = F(3,1)**2+F(2,1)**2+F(1,1)**2
tt88 = 2*tt13
tt89 = (-F(1,1)*tt36)-F(2,1)*tt30+(F(1,1)*F(2,3)+F(1,3)*F(2,1))*t&
&t22-2*F(1,3)*F(2,3)*tt87
tt90 = (-F(1,1)*tt42)-F(3,1)*tt30+(F(1,1)*F(3,3)+F(1,3)*F(3,1))*t&
&t22-2*F(1,3)*tt87*F(3,3)
tt91 = -F(2,1)*F(2,3)
tt92 = -F(3,1)*F(3,3)
tt93 = -2*tt8
tt94 = F(1,1)*tt28-F(1,1)*tt52+tt87*(tt93+2*F(1,2)*F(1,3))+(tt26+&
&tt25)*tt22-tt27*(tt92+tt91)
tt95 = (-F(1,1)*tt57)+F(2,1)*tt28+(F(1,1)*F(2,2)-2*F(1,2)*F(2,1))&
&*tt22-(2*F(1,1)*F(2,3)-F(1,3)*F(2,1))*tt27+(4*F(1,2)*F(2,3)+tt34)&
&*tt87
tt96 = (-F(1,1)*tt62)+F(3,1)*tt28+(F(1,1)*F(3,2)-2*F(1,2)*F(3,1))&
&*tt22+tt87*(4*F(1,2)*F(3,3)+tt40)-tt27*(2*F(1,1)*F(3,3)-F(1,3)*F(&
&3,1))
tt97 = (-F(2,1)*tt42)-F(3,1)*tt36+(F(2,1)*F(3,3)+F(2,3)*F(3,1))*t&
&t22-2*F(2,3)*tt87*F(3,3)
tt98 = F(1,1)*tt35-F(2,1)*tt52+(F(1,2)*F(2,1)-2*F(1,1)*F(2,2))*tt&
&22-(2*F(1,3)*F(2,1)-F(1,1)*F(2,3))*tt27+(tt66+4*F(1,3)*F(2,2))*tt&
&87
tt99 = -F(1,1)*F(1,3)
tt100 = F(2,1)*tt35-F(2,1)*tt57+tt87*(tt93+2*F(2,2)*F(2,3))+(tt26&
&+tt24)*tt22-tt27*(tt92+tt99)
tt101 = (-F(2,1)*tt62)+F(3,1)*tt35+(F(2,1)*F(3,2)-2*F(2,2)*F(3,1)&
&)*tt22+tt87*(4*F(2,2)*F(3,3)+tt70)-tt27*(2*F(2,1)*F(3,3)-F(2,3)*F&
&(3,1))
tt102 = F(1,1)*tt41-F(3,1)*tt52+(F(1,2)*F(3,1)-2*F(1,1)*F(3,2))*t&
&t22+tt87*(tt78+4*F(1,3)*F(3,2))-tt27*(2*F(1,3)*F(3,1)-F(1,1)*F(3,&
&3))
tt103 = F(2,1)*tt41-F(3,1)*tt57+(F(2,2)*F(3,1)-2*F(2,1)*F(3,2))*t&
&t22+tt87*(tt80+4*F(2,3)*F(3,2))-tt27*(2*F(2,3)*F(3,1)-F(2,1)*F(3,&
&3))
tt104 = F(3,1)*tt41-F(3,1)*tt62+tt87*(tt93+2*F(3,2)*F(3,3))+(tt25&
&+tt24)*tt22-(tt91+tt99)*tt27
tt105 = 2*tt27
tt106 = 2*tt4
tt107 = F(1,1)*tt55+F(2,1)*tt45-((-F(1,1)*F(2,2))-F(1,2)*F(2,1))*&
&tt27-2*F(1,2)*F(2,2)*tt87
tt108 = F(1,1)*tt60+F(3,1)*tt45-((-F(1,1)*F(3,2))-F(1,2)*F(3,1))*&
&tt27-2*F(1,2)*tt87*F(3,2)
tt109 = F(2,1)*tt60+F(3,1)*tt55-((-F(2,1)*F(3,2))-F(2,2)*F(3,1))*&
&tt27-2*F(2,2)*tt87*F(3,2)
hes(1,1) = tt15-2*F(1,2)*tt14+2*F(1,3)*tt9
hes(1,2) = tt18
hes(1,3) = tt21
hes(1,4) = tt32
hes(1,5) = tt38
hes(1,6) = tt44
hes(1,7) = tt54
hes(1,8) = tt59
hes(1,9) = tt64
hes(2,1) = tt18
hes(2,2) = tt15-2*F(2,2)*tt17+2*F(2,3)*tt16
hes(2,3) = tt65
hes(2,4) = tt67
hes(2,5) = tt68
hes(2,6) = tt71
hes(2,7) = tt72
hes(2,8) = tt75
hes(2,9) = tt77
hes(3,1) = tt21
hes(3,2) = tt65
hes(3,3) = tt15-2*F(3,2)*tt20+2*F(3,3)*tt19
hes(3,4) = tt79
hes(3,5) = tt81
hes(3,6) = tt82
hes(3,7) = tt83
hes(3,8) = tt84
hes(3,9) = tt85
hes(4,1) = tt32
hes(4,2) = tt67
hes(4,3) = tt79
hes(4,4) = (-2*F(1,1)*tt30)+tt87*(tt88-2*tt10)+tt22*(tt86+2*F(1,1&
&)*F(1,3))
hes(4,5) = tt89
hes(4,6) = tt90
hes(4,7) = tt94
hes(4,8) = tt95
hes(4,9) = tt96
hes(5,1) = tt38
hes(5,2) = tt68
hes(5,3) = tt81
hes(5,4) = tt89
hes(5,5) = (-2*F(2,1)*tt36)+tt87*(tt88-2*tt11)+tt22*(tt86+2*F(2,1&
&)*F(2,3))
hes(5,6) = tt97
hes(5,7) = tt98
hes(5,8) = tt100
hes(5,9) = tt101
hes(6,1) = tt44
hes(6,2) = tt71
hes(6,3) = tt82
hes(6,4) = tt90
hes(6,5) = tt97
hes(6,6) = (-2*F(3,1)*tt42)+tt87*(tt88-2*tt12)+tt22*(tt86+2*F(3,1&
&)*F(3,3))
hes(6,7) = tt102
hes(6,8) = tt103
hes(6,9) = tt104
hes(7,1) = tt54
hes(7,2) = tt72
hes(7,3) = tt83
hes(7,4) = tt94
hes(7,5) = tt98
hes(7,6) = tt102
hes(7,7) = 2*F(1,1)*tt45+tt87*(tt106-2*tt1)-tt27*(tt105-2*F(1,1)*&
&F(1,2))
hes(7,8) = tt107
hes(7,9) = tt108
hes(8,1) = tt59
hes(8,2) = tt75
hes(8,3) = tt84
hes(8,4) = tt95
hes(8,5) = tt100
hes(8,6) = tt103
hes(8,7) = tt107
hes(8,8) = 2*F(2,1)*tt55+tt87*(tt106-2*tt2)-tt27*(tt105-2*F(2,1)*&
&F(2,2))
hes(8,9) = tt109
hes(9,1) = tt64
hes(9,2) = tt77
hes(9,3) = tt85
hes(9,4) = tt96
hes(9,5) = tt101
hes(9,6) = tt104
hes(9,7) = tt108
hes(9,8) = tt109
hes(9,9) = 2*F(3,1)*tt60+tt87*(tt106-2*tt3)-tt27*(tt105-2*F(3,1)*&
&F(3,2))
END
