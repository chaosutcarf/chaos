// clang-format off
void linear_elas_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void linear_elas_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void linear_elas_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void stvk_elas_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void stvk_elas_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void stvk_elas_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void coro_elas_2d_val_(double *val, const double *F, const double *lam, const double *mu, const double *R);
void coro_elas_2d_jac_(double *jac, const double *F, const double *lam, const double *mu, const double *R);
void coro_elas_2d_hes_(double *hes, const double *F, const double *lam, const double *mu, const double *R);
void mcadams_coro_elas_2d_val_(double *val, const double *F, const double *lam, const double *mu, const double *R);
void mcadams_coro_elas_2d_jac_(double *jac, const double *F, const double *lam, const double *mu, const double *R);
void mcadams_coro_elas_2d_hes_(double *hes, const double *F, const double *lam, const double *mu, const double *R);
void stomakhin_fixedcoro_elas_2d_val_(double *val, const double *F, const double *lam, const double *mu, const double *R);
void stomakhin_fixedcoro_elas_2d_jac_(double *jac, const double *F, const double *lam, const double *mu, const double *R);
void stomakhin_fixedcoro_elas_2d_hes_(double *hes, const double *F, const double *lam, const double *mu, const double *R);
void bonet08_neohookean_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void bonet08_neohookean_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void bonet08_neohookean_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void ogden97_neohookean_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void ogden97_neohookean_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void ogden97_neohookean_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void bower09_neohookean_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void bower09_neohookean_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void bower09_neohookean_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void pixar18_rest_stable_neohookean_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void pixar18_rest_stable_neohookean_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void pixar18_rest_stable_neohookean_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void pixar18_neohookean_2d_val_(double *val, const double *F, const double *lam, const double *mu);
void pixar18_neohookean_2d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void pixar18_neohookean_2d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void linear_elas_lam_2d_val_(double *val, const double *F);
void linear_elas_lam_2d_jac_(double *jac, const double *F);
void linear_elas_lam_2d_hes_(double *hes, const double *F);
void linear_elas_mu_2d_val_(double *val, const double *F);
void linear_elas_mu_2d_jac_(double *jac, const double *F);
void linear_elas_mu_2d_hes_(double *hes, const double *F);
void stvk_elas_lam_2d_val_(double *val, const double *F);
void stvk_elas_lam_2d_jac_(double *jac, const double *F);
void stvk_elas_lam_2d_hes_(double *hes, const double *F);
void stvk_elas_mu_2d_val_(double *val, const double *F);
void stvk_elas_mu_2d_jac_(double *jac, const double *F);
void stvk_elas_mu_2d_hes_(double *hes, const double *F);
void coro_elas_lam_2d_val_(double *val, const double *F, const double *R);
void coro_elas_lam_2d_jac_(double *jac, const double *F, const double *R);
void coro_elas_lam_2d_hes_(double *hes, const double *F, const double *R);
void coro_elas_mu_2d_val_(double *val, const double *F, const double *R);
void coro_elas_mu_2d_jac_(double *jac, const double *F, const double *R);
void coro_elas_mu_2d_hes_(double *hes, const double *F, const double *R);
void mcadams_coro_elas_lam_2d_val_(double *val, const double *F, const double *R);
void mcadams_coro_elas_lam_2d_jac_(double *jac, const double *F, const double *R);
void mcadams_coro_elas_lam_2d_hes_(double *hes, const double *F, const double *R);
void mcadams_coro_elas_mu_2d_val_(double *val, const double *F, const double *R);
void mcadams_coro_elas_mu_2d_jac_(double *jac, const double *F, const double *R);
void mcadams_coro_elas_mu_2d_hes_(double *hes, const double *F, const double *R);
void stomakhin_fixedcoro_elas_lam_2d_val_(double *val, const double *F, const double *R);
void stomakhin_fixedcoro_elas_lam_2d_jac_(double *jac, const double *F, const double *R);
void stomakhin_fixedcoro_elas_lam_2d_hes_(double *hes, const double *F, const double *R);
void stomakhin_fixedcoro_elas_mu_2d_val_(double *val, const double *F, const double *R);
void stomakhin_fixedcoro_elas_mu_2d_jac_(double *jac, const double *F, const double *R);
void stomakhin_fixedcoro_elas_mu_2d_hes_(double *hes, const double *F, const double *R);
void bonet08_neohookean_lam_2d_val_(double *val, const double *F);
void bonet08_neohookean_lam_2d_jac_(double *jac, const double *F);
void bonet08_neohookean_lam_2d_hes_(double *hes, const double *F);
void bonet08_neohookean_mu_2d_val_(double *val, const double *F);
void bonet08_neohookean_mu_2d_jac_(double *jac, const double *F);
void bonet08_neohookean_mu_2d_hes_(double *hes, const double *F);
void ogden97_neohookean_lam_2d_val_(double *val, const double *F);
void ogden97_neohookean_lam_2d_jac_(double *jac, const double *F);
void ogden97_neohookean_lam_2d_hes_(double *hes, const double *F);
void ogden97_neohookean_mu_2d_val_(double *val, const double *F);
void ogden97_neohookean_mu_2d_jac_(double *jac, const double *F);
void ogden97_neohookean_mu_2d_hes_(double *hes, const double *F);
void bower09_neohookean_lam_2d_val_(double *val, const double *F);
void bower09_neohookean_lam_2d_jac_(double *jac, const double *F);
void bower09_neohookean_lam_2d_hes_(double *hes, const double *F);
void bower09_neohookean_mu_2d_val_(double *val, const double *F);
void bower09_neohookean_mu_2d_jac_(double *jac, const double *F);
void bower09_neohookean_mu_2d_hes_(double *hes, const double *F);
void pixar18_rest_stable_neohookean_lam_2d_val_(double *val, const double *F);
void pixar18_rest_stable_neohookean_lam_2d_jac_(double *jac, const double *F);
void pixar18_rest_stable_neohookean_lam_2d_hes_(double *hes, const double *F);
void pixar18_rest_stable_neohookean_mu_2d_val_(double *val, const double *F);
void pixar18_rest_stable_neohookean_mu_2d_jac_(double *jac, const double *F);
void pixar18_rest_stable_neohookean_mu_2d_hes_(double *hes, const double *F);
void pixar18_neohookean_lam_2d_val_(double *val, const double *F);
void pixar18_neohookean_lam_2d_jac_(double *jac, const double *F);
void pixar18_neohookean_lam_2d_hes_(double *hes, const double *F);
void pixar18_neohookean_mu_2d_val_(double *val, const double *F);
void pixar18_neohookean_mu_2d_jac_(double *jac, const double *F);
void pixar18_neohookean_mu_2d_hes_(double *hes, const double *F);
void small_general_linear_elas_2d_val_(double *val, const double *F, const double *C);
void small_general_linear_elas_2d_jac_(double *jac, const double *F, const double *C);
void small_general_linear_elas_2d_hes_(double *hes, const double *F, const double *C);
void green_general_linear_elas_2d_val_(double *val, const double *F, const double *C);
void green_general_linear_elas_2d_jac_(double *jac, const double *F, const double *C);
void green_general_linear_elas_2d_hes_(double *hes, const double *F, const double *C);
void coro_general_linear_elas_2d_val_(double *val, const double *F, const double *C, const double *R);
void coro_general_linear_elas_2d_jac_(double *jac, const double *F, const double *C, const double *R);
void coro_general_linear_elas_2d_hes_(double *hes, const double *F, const double *C, const double *R);
void I_C_2d_val_(double *val, const double *F);
void I_C_2d_jac_(double *jac, const double *F);
void I_C_2d_hes_(double *hes, const double *F);
void II_C_2d_val_(double *val, const double *F);
void II_C_2d_jac_(double *jac, const double *F);
void II_C_2d_hes_(double *hes, const double *F);
void III_C_2d_val_(double *val, const double *F);
void III_C_2d_jac_(double *jac, const double *F);
void III_C_2d_hes_(double *hes, const double *F);
void linear_elas_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void linear_elas_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void linear_elas_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void stvk_elas_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void stvk_elas_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void stvk_elas_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void coro_elas_3d_val_(double *val, const double *F, const double *lam, const double *mu, const double *R);
void coro_elas_3d_jac_(double *jac, const double *F, const double *lam, const double *mu, const double *R);
void coro_elas_3d_hes_(double *hes, const double *F, const double *lam, const double *mu, const double *R);
void mcadams_coro_elas_3d_val_(double *val, const double *F, const double *lam, const double *mu, const double *R);
void mcadams_coro_elas_3d_jac_(double *jac, const double *F, const double *lam, const double *mu, const double *R);
void mcadams_coro_elas_3d_hes_(double *hes, const double *F, const double *lam, const double *mu, const double *R);
void stomakhin_fixedcoro_elas_3d_val_(double *val, const double *F, const double *lam, const double *mu, const double *R);
void stomakhin_fixedcoro_elas_3d_jac_(double *jac, const double *F, const double *lam, const double *mu, const double *R);
void stomakhin_fixedcoro_elas_3d_hes_(double *hes, const double *F, const double *lam, const double *mu, const double *R);
void bonet08_neohookean_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void bonet08_neohookean_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void bonet08_neohookean_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void ogden97_neohookean_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void ogden97_neohookean_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void ogden97_neohookean_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void bower09_neohookean_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void bower09_neohookean_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void bower09_neohookean_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void pixar18_rest_stable_neohookean_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void pixar18_rest_stable_neohookean_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void pixar18_rest_stable_neohookean_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void pixar18_neohookean_3d_val_(double *val, const double *F, const double *lam, const double *mu);
void pixar18_neohookean_3d_jac_(double *jac, const double *F, const double *lam, const double *mu);
void pixar18_neohookean_3d_hes_(double *hes, const double *F, const double *lam, const double *mu);
void linear_elas_lam_3d_val_(double *val, const double *F);
void linear_elas_lam_3d_jac_(double *jac, const double *F);
void linear_elas_lam_3d_hes_(double *hes, const double *F);
void linear_elas_mu_3d_val_(double *val, const double *F);
void linear_elas_mu_3d_jac_(double *jac, const double *F);
void linear_elas_mu_3d_hes_(double *hes, const double *F);
void stvk_elas_lam_3d_val_(double *val, const double *F);
void stvk_elas_lam_3d_jac_(double *jac, const double *F);
void stvk_elas_lam_3d_hes_(double *hes, const double *F);
void stvk_elas_mu_3d_val_(double *val, const double *F);
void stvk_elas_mu_3d_jac_(double *jac, const double *F);
void stvk_elas_mu_3d_hes_(double *hes, const double *F);
void coro_elas_lam_3d_val_(double *val, const double *F, const double *R);
void coro_elas_lam_3d_jac_(double *jac, const double *F, const double *R);
void coro_elas_lam_3d_hes_(double *hes, const double *F, const double *R);
void coro_elas_mu_3d_val_(double *val, const double *F, const double *R);
void coro_elas_mu_3d_jac_(double *jac, const double *F, const double *R);
void coro_elas_mu_3d_hes_(double *hes, const double *F, const double *R);
void mcadams_coro_elas_lam_3d_val_(double *val, const double *F, const double *R);
void mcadams_coro_elas_lam_3d_jac_(double *jac, const double *F, const double *R);
void mcadams_coro_elas_lam_3d_hes_(double *hes, const double *F, const double *R);
void mcadams_coro_elas_mu_3d_val_(double *val, const double *F, const double *R);
void mcadams_coro_elas_mu_3d_jac_(double *jac, const double *F, const double *R);
void mcadams_coro_elas_mu_3d_hes_(double *hes, const double *F, const double *R);
void stomakhin_fixedcoro_elas_lam_3d_val_(double *val, const double *F, const double *R);
void stomakhin_fixedcoro_elas_lam_3d_jac_(double *jac, const double *F, const double *R);
void stomakhin_fixedcoro_elas_lam_3d_hes_(double *hes, const double *F, const double *R);
void stomakhin_fixedcoro_elas_mu_3d_val_(double *val, const double *F, const double *R);
void stomakhin_fixedcoro_elas_mu_3d_jac_(double *jac, const double *F, const double *R);
void stomakhin_fixedcoro_elas_mu_3d_hes_(double *hes, const double *F, const double *R);
void bonet08_neohookean_lam_3d_val_(double *val, const double *F);
void bonet08_neohookean_lam_3d_jac_(double *jac, const double *F);
void bonet08_neohookean_lam_3d_hes_(double *hes, const double *F);
void bonet08_neohookean_mu_3d_val_(double *val, const double *F);
void bonet08_neohookean_mu_3d_jac_(double *jac, const double *F);
void bonet08_neohookean_mu_3d_hes_(double *hes, const double *F);
void ogden97_neohookean_lam_3d_val_(double *val, const double *F);
void ogden97_neohookean_lam_3d_jac_(double *jac, const double *F);
void ogden97_neohookean_lam_3d_hes_(double *hes, const double *F);
void ogden97_neohookean_mu_3d_val_(double *val, const double *F);
void ogden97_neohookean_mu_3d_jac_(double *jac, const double *F);
void ogden97_neohookean_mu_3d_hes_(double *hes, const double *F);
void bower09_neohookean_lam_3d_val_(double *val, const double *F);
void bower09_neohookean_lam_3d_jac_(double *jac, const double *F);
void bower09_neohookean_lam_3d_hes_(double *hes, const double *F);
void bower09_neohookean_mu_3d_val_(double *val, const double *F);
void bower09_neohookean_mu_3d_jac_(double *jac, const double *F);
void bower09_neohookean_mu_3d_hes_(double *hes, const double *F);
void pixar18_rest_stable_neohookean_lam_3d_val_(double *val, const double *F);
void pixar18_rest_stable_neohookean_lam_3d_jac_(double *jac, const double *F);
void pixar18_rest_stable_neohookean_lam_3d_hes_(double *hes, const double *F);
void pixar18_rest_stable_neohookean_mu_3d_val_(double *val, const double *F);
void pixar18_rest_stable_neohookean_mu_3d_jac_(double *jac, const double *F);
void pixar18_rest_stable_neohookean_mu_3d_hes_(double *hes, const double *F);
void pixar18_neohookean_lam_3d_val_(double *val, const double *F);
void pixar18_neohookean_lam_3d_jac_(double *jac, const double *F);
void pixar18_neohookean_lam_3d_hes_(double *hes, const double *F);
void pixar18_neohookean_mu_3d_val_(double *val, const double *F);
void pixar18_neohookean_mu_3d_jac_(double *jac, const double *F);
void pixar18_neohookean_mu_3d_hes_(double *hes, const double *F);
void small_general_linear_elas_3d_val_(double *val, const double *F, const double *C);
void small_general_linear_elas_3d_jac_(double *jac, const double *F, const double *C);
void small_general_linear_elas_3d_hes_(double *hes, const double *F, const double *C);
void green_general_linear_elas_3d_val_(double *val, const double *F, const double *C);
void green_general_linear_elas_3d_jac_(double *jac, const double *F, const double *C);
void green_general_linear_elas_3d_hes_(double *hes, const double *F, const double *C);
void coro_general_linear_elas_3d_val_(double *val, const double *F, const double *C, const double *R);
void coro_general_linear_elas_3d_jac_(double *jac, const double *F, const double *C, const double *R);
void coro_general_linear_elas_3d_hes_(double *hes, const double *F, const double *C, const double *R);
void I_C_3d_val_(double *val, const double *F);
void I_C_3d_jac_(double *jac, const double *F);
void I_C_3d_hes_(double *hes, const double *F);
void II_C_3d_val_(double *val, const double *F);
void II_C_3d_jac_(double *jac, const double *F);
void II_C_3d_hes_(double *hes, const double *F);
void III_C_3d_val_(double *val, const double *F);
void III_C_3d_jac_(double *jac, const double *F);
void III_C_3d_hes_(double *hes, const double *F);
// clang-format on
