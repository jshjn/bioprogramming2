SELECT
  variant.var_id,
  gene.gene_id
FROM variant
JOIN gene
  ON variant.chrom=gene.chrom
 AND variant.pos BETWEEN gene.start_pos AND gene.end_pos;