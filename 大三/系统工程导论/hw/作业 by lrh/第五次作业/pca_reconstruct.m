function recon_data = pca_reconstruct(pcs, cprs_data, cprs_c)
n = size(cprs_c{1},2) - 1;
EX = cprs_c{1}(1:n);
SX = cprs_c{2}(1:n);
recon_data = cprs_data * (pcs') .* SX + EX;