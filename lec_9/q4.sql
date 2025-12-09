SELECT
  expression.tpm,
  sample.tissue,
  sample.disease
FROM expression
JOIN sample
  ON expression.sample_id=sample.sample_id
WHERE expression.gene_id='G1';