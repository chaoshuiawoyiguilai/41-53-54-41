data = xlsread('counties.xlsx');
rerr = 0.05;
alpha = 0.5;
[pcs, cprs_data, cprs_c] = pca_compress(data, rerr);
recon_data = pca_reconstruct(pcs, cprs_data, cprs_c);
fprintf("1)PCA\n"); 
linear_regression_pca(data, alpha, rerr);
fprintf("2)病态回归\n"); 
linear_regression_ill_cond(data, alpha, rerr);
