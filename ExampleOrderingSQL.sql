SELECT 
  * 
FROM
  VG_INSTANCE_DATA_VG_CTY_MID_DUMMY 
WHERE
/* The following WHERE clause is semantically equivalent to the simpler clause "WHERE a <= b AND b <= c ...", with a, b, c, ...
each corresponding to the set of primary key fields of the unit of analysis for that DMU category with multiplicity greater than 1
(i.e. for the DMU category which the user has cranked up beyond the minimum via the spin control in the user interface),
but it also handles the possibility of NULL for any of these primary key fields.
This WHERE clause has the effect of including only rows where all NULL columns in primary keys fields appear to the right,
and where the non-NULL primary keys increase from left to right.
When there is more than one field in the unit of analysis corresponding to the DMU category with multiplicity greater than one, 
the "<=" comparison is expanded to be based on the first field which is not equal. */ 
(
    CASE
      WHEN Dummy IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      AND DATETIME_ROW_START IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      THEN 1 
      WHEN Dummy IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      AND DATETIME_ROW_START IS NOT NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      THEN 0 
      WHEN Dummy IS NOT NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      AND DATETIME_ROW_START IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      THEN 1 
      ELSE Dummy <= DATETIME_ROW_START 
    END
  ) 
  AND (
    CASE
      WHEN DATETIME_ROW_START IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      AND DATETIME_ROW_END IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      THEN 1 
      WHEN DATETIME_ROW_START IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      AND DATETIME_ROW_END IS NOT NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      THEN 0 
      WHEN DATETIME_ROW_START IS NOT NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      AND DATETIME_ROW_END IS NULL /* For units of analysis with more than one field in this DMU category for the primary key, checking the first field suffices as a NULL check */
      THEN 1 
      ELSE DATETIME_ROW_START <= DATETIME_ROW_END 
    END
  )
  /* ORDER BY the multiplicities of the DMU category with multiplicity greater than 1, from lowest to highest multiplicity.
  If there is more than one primary key column per multiplicity, then order by the first field across multiplicities, 
  then the second field across multiplicities, and so on. */
ORDER BY Dummy,
  DATETIME_ROW_START,
  DATETIME_ROW_END 