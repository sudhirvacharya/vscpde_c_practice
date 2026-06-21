| Declaration | Meaning | Correct Expanded Form |
|---|---|---|
| `typedef char *pc` | pointer to char | `char *pc` |
| `typedef pc fpc()` | function returning pointer to char | `char *fpc()` |
| `typedef fpc *pfpc` | pointer to function returning `char *` | `char *(*pfpc)()` |
| `typedef pfpc fpfpc()` | function returning pointer to function returning `char *` | `char *(*fpfpc())()` |
| `typedef fpfpc *pfpfpc` | pointer to function returning pointer to function returning `char *` | `char *(*(*pfpfpc)())()` |
| `pfpfpc a[N]` | array of N pointers to functions returning pointers to functions returning `char *` | `char *(*(*a[N])())()` |