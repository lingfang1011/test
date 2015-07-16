﻿/*!
* \file Aris_DynKer.h
* \brief 概述
* \author 潘阳
* \version 1.0.0.0
* \date 2014/4/5
*/

#ifndef Aris_DynKer_H
#define Aris_DynKer_H

#ifndef PI
#define PI 3.141592653589793
#endif

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

#include <Aris_XML.h>
#include <Aris_ExpCal.h>


namespace Aris
{
	namespace DynKer
	{
		void s_dgeev(int n, double* a, int lda, double* wr, double* wi);
		
		void dsp(const double *p, const int m, const int n, const int begin_row = 0, const int begin_col = 0, int ld = 0);
		void dlmwrite(const char *FileName, const double *pMatrix, const unsigned int m, const unsigned int n);
		void dlmread(const char *FileName, double *pMatrix);
		
		inline int s_sgn(double x)
		{
			if (x > 0)
			{
				return 1;
			}
			else if (x == 0)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		inline int s_sgn2(double x)
		{
			return x < 0 ? -1 : 1;
		}
		inline double s_max(double a, double b)
		{
			return a > b ? a : b;
		}
		/*please make sure that length>=2 and data is not nullptr*/
		inline double s_max(const double *data, unsigned length, unsigned *id = nullptr)
		{
			double rVar=data[0];
			unsigned locID = 0;
			
			for (unsigned i = 1; i < length; ++i)
			{
				if (data[i] > rVar)
				{
					rVar = data[i];
					locID = i;
				}
			}

			if (id != nullptr)
			{
				*id = locID;
			}

			return rVar;
		}
		inline double s_max_abs(const double *data, unsigned length, unsigned *id = nullptr)
		{
			double rVar = std::abs(data[0]);
			unsigned locID = 0;

			for (unsigned i = 1; i < length; ++i)
			{
				if (std::abs(data[i]) > rVar)
				{
					rVar = std::abs(data[i]);
					locID = i;
				}
			}

			if (id != nullptr)
			{
				*id = locID;
			}

			return rVar;
		}
		inline double s_min(double a, double b)
		{
			return a < b ? a : b;
		}
		/*please make sure that length>=2 and data is not nullptr*/
		inline double s_min(const double *data, unsigned length, unsigned *id = nullptr)
		{
			double rVar = data[0];
			unsigned locID = 0;

			for (unsigned i = 1; i < length; ++i)
			{
				if (data[i] < rVar)
				{
					rVar = data[i];
					locID = i;
				}
			}

			if (id != nullptr)
			{
				*id = locID;
			}

			return rVar;
		}


		void s_cro3(const double *cro_vec_in, const double *vec_in, double *vec_out);
		void s_cm3(const double *cro_vec_in, double *cm_out);

		void s_inv_pm(const double *pm_in, double *pm_out);
		void s_inv_im(const double *im_in, double *im_out);
		void s_axes2pm(const double *origin, const double *firstAxisPnt, const double *secondAxisPnt, double *pm_out, const char *axesOrder = "xy");
		void s_pm2pe(const double *pm_in, double *pe_out, const char *EurType="313");
		void s_pe2pm(const double *pe_in, double *pm_out, const char *EurType="313");
		void s_pm2pr(const double *pm_in, double *pr_out);
		void s_pr2pm(const double *pr_in, double *pm_out);
		void s_pm2pq(const double *pm_in, double *qp_out);
		void s_pq2pm(const double *pq_in, double *pm_out);
		void s_vq2v(const double *pq_in, const double *vq_in, double *v_out);
		void s_v2vq(const double *pm_in, const double *v_in, double *vq_out);
		void s_tmf(const double *pm_in, double *tm_out);
		void s_tmv(const double *pm_in, double *tmd_out);
		void s_cmf(const double *vel_in, double *cm_out);
		void s_cmv(const double *vel_in, double *cmd_out);
		void s_i2i(const double *from_pm_in, const double *from_im_in, double *to_im_out);
		/** \brief 计算点加速度
		*
		* 用来将6维空间速度从一个坐标系中转化到另一个坐标系中。例如将B坐标系中的速度转换到A坐标系中。
		*
		* \param relative_pm_in 表示两个坐标系之间的位姿矩阵。即B相对于A的位姿矩阵。
		* \param relative_vel_in 表示两个坐标系之间的相对速度。即B相对于A的空间速度向量，这个向量在坐标系A中表达。
		* \param from_vel_in 表示坐标系B中待转换的速度向量。
		* \param to_vel_out 表示转换完成的速度向量，即A坐标系中的速度向量。
		*/
		void s_v2v(const double *relative_pm_in, const double *relative_vel_in, const double *from_vel_in, double *to_vel_out);
		void s_a2a(const double *relative_pm_in, const double *relative_vel_in, const double *relative_acc_in,
			const double *from_vel_in, const double *from_acc_in, double *to_acc_out, double *to_vel_out = 0);
		void s_pnt2pnt(const double *relative_pm_in, const double *from_pnt, double *to_pnt_out);
		/** \brief 计算点加速度
		*
		* 转化点速度的坐标系。
		*
		*/
		void s_pv2pv(const double *relative_pm_in, const double *relative_vel_in, 
			const double *from_pnt, const double *from_pv, double *to_pv_out, double *to_pnt_out = 0);
		void s_pa2pa(const double *relative_pm_in, const double *relative_vel_in, const double *inv_relative_acc_in,
			const double *from_pnt, const double *from_pv, const double *from_pa,
			double *to_pa_out, double *to_pv_out = 0, double *to_pnt_out = 0);
		void s_inv_pv2pv(const double *inv_relative_pm_in, const double *inv_relative_vel_in,
			const double *from_pnt, const double *from_pv, double *to_pv_out, double *to_pnt_out = 0);
		void s_inv_pa2pa(const double *inv_relative_pm_in, const double *inv_relative_vel_in, const double *inv_relative_acc_in,
			const double *from_pnt, const double *from_pv, const double *from_pa, 
			double *to_pa_out, double *to_pv_out = 0, double *to_pnt_out = 0);
		void s_mass2im(const double mass_in, const double * inertia_in, const double *pm_in, double *im_out);
		void s_gamma2im(const double * gamma_in, double *im_out);
		void s_im2gamma(const double * im_in, double *gamma_out);

		void s_pv(const double *pnt_in, const double *vel_in, double *pv_out);
		/** \brief 计算点加速度
		*
		* 根据数据点位置、空间速度和空间加速度来计算该点的加速度。
		*
		*/
		void s_pa(const double *pnt_in, const double *vel_in, const double *acc_in, double *pnt_acc_out);

		void s_block_cpy(const int &block_size_m, const int &block_size_n,
			const double *from_mtrx, const int &fm_begin_row, const int &fm_begin_col, const int &fm_ld,
			double *to_mtrx, const int &tm_begin_row, const int &tm_begin_col, const int &tm_ld);

		void s_dlt_col(const int &dlt_col_num, const int *col_index, const int &m, const int &n, double *A, const int &ldA);

		void s_pm_dot_pm(const double *pm1_in, const double *pm2_in, double *pm_out);
		void s_inv_pm_dot_pm(const double *inv_pm1_in, const double *pm2_in, double *pm_out);
		void s_pm_dot_pnt(const double *pm_in, const double *pos_in, double *pos_out);
		void s_inv_pm_dot_pnt(const double *pm_in, const double *pos_in, double *pos_out);
		void s_tmf_dot_fce(const double *tm_in, const double *fce_in, double *fce_out);
		void s_tmv_dot_vel(const double *tmd_in, const double *vel_in, double *vel_out);
		void s_im_dot_gravity(const double *im_in, const double *gravity, double *gravity_fce_out);

		void s_v_cro_pm(const double *v_in, const double *pm_in, double *vpm_out);

		void s_dscal(const int n, const double a, double *x, const int incx);
		double s_dnrm2(const int n, const double *x, const int incx);
		void s_daxpy(const int N, const double alpha, const double *X, const int incX, double *Y, const int incY);
		void s_swap(const int N, double *X, const int incX, double *Y, const int incY);
		void s_transpose(const int m, const int n, const double *A, const int ldA, double *B_out, const int ldB);

		void s_dgeinv(const int n, double* A,const int lda, int *ipiv);
		void s_dgemm(int m, int n, int k, double alpha, const double* A, int lda, const double* B, int ldb, double beta, double *C, int ldc);
		void s_dgemmTN(int m, int n, int k, double alpha, const double* A, int lda, const double* B, int ldb, double beta, double *C, int ldc);
		void s_dgemmNT(int m, int n, int k, double alpha, const double* A, int lda, const double* B, int ldb, double beta, double *C, int ldc);
		void s_dgesv(int n, int nrhs, double* a, int lda, int* ipiv, double* b, int ldb);
		void s_dgesvT(int n, int nrhs, double* a, int lda, int* ipiv, double* b, int ldb);
		void s_dgelsd(int m, int n, int nrhs, double* a, int lda, double* b, int ldb, double* s, double rcond, int* rank);
		void s_dgelsdT(int m, int n, int nrhs, double* a, int lda, double* b, int ldb, double* s, double rcond, int* rank);

		void s_akima(unsigned inNum, unsigned outNum, const double *x_in, const double *y_in, const double *x, double *y,unsigned order=0);
	}
}




























#endif
