sort < a | cat b - | tr A-Z a-z > c
(sort -k2 d - < a | uniq -c > e)
diff a #c > f

a&&b||
 c &&
  d | e && f|