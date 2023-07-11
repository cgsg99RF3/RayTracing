Ўрифты...	

bmfont64.exe --> текстура с символами + файл описани€ символов (*.fnt)

--> будем получать *.g3df

про отрисовку букв:
(см. изображение)
»де€: весь шрифт загрузить в vg4PRIMS как 256 примитивов (1 на каждый символ)
+ хранить смещение до следующего символа


—труктура формата G3DF:

DWORD Sign;              -- сигнатура Ц признак файла Ц "G3DF"
DWORD LineH;             -- высота шрифта (строки) в пиксел€х
DWORD BaseH;             -- рассто€ние до базовой линии в пиксел€х
FLT AdvancedX[256];      -- смещение к следующему символу дл€ каждого символа из шрифта
                            (0 Ц если символа нет)
vg4VERTEX Chars[256][4]; -- угловые точки пр€моугольника с символом
                            (lefttop-leftbottom-roghttop-rrightbottom)
DWORD W, H;              -- размеры текстуры в пиксел€х
W * H * 4 байт текстура с alpha-каналом


/* Font description structure */
typedef struct tagvg4FONT
{
  DWORD LineH, BaseH; /* Font line height and base line height in pixels */
  FLT AdvanceX[256];  /* Every letter shift right value (0 if no letter present) */
} vg4FONT; 

/* Current font description */

/* Font data */
static vg4FONT VG4_RndFntFont;

/* Font characters primitives */
static vg4PRIM VG4_RndFntChars[256];

/* Font material */
static INT VG4_RndFntMtlNo;

/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL VG4_RndFntLoad( CHAR *FileName )
{
  FILE *F;
  INT i;
  DWORD Sign, W, H, *tex;
  vg4VERTEX Chars[256][4];
  vg4MATERIAL mtl;

  if ((F = fopen(FileName, "rb")) == NULL)
   return FALSE;
  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return FALSE;
  }
  fread(&VG4_RndFntFont, sizeof(vg4FONT), 1, F);
  fread(&Chars, sizeof(vg4VERTEX), 4 * 256, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);

  mtl = VG4_RndMtlGetDef();
  strncpy(mtl.Name, FileName, VG4_STR_MAX - 1);
  if ((tex = malloc(W * H * 4)))
  {
    fread(tex, 4, W * H, F);
    mtl.Tex[0] = VG4_RndTexAddImg(FileName, W, H, 4, tex);
    free(tex);
  }
  mtl.ShdNo = VG4_RndShdAdd("FONT");
  VG4_RndFntMtlNo = VG4_RndMtlAdd(&mtl);

  for (i = 0; i < 256; i++)
  {
    VG4_RndPrimFree(&VG4_RndFntChars[i]);
    VG4_RndPrimCreate(&VG4_RndFntChars[i], VG4_RND_PRIM_TRISTRIP, Chars[i], 4, NULL, 0);
    VG4_RndFntChars[i].MtlNo = VG4_RndFntMtlNo;
  }

  fclose(F);
  return TRUE;
} /* End of 'VG4_RndFntLoad' function */

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndFntInit( CHAR *FileName )
{
  VG4_RndFntLoad("BIN/FONTS/Consolas.g3df");
} /* End of 'VG4_RndFntInit' function */

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID VG4_RndFntClose( CHAR *FileName )
{
  INT i;

  for (i = 0; i < 256; i++)
    VG4_RndPrimFree(&VG4_RndFntChars[i]);
  memset(VG4_RndFntChars, 0, sizeof(VG4_RndFntChars));
} /* End of 'VG4_RndFntInit' function */

/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 * RETURNS: None.
 */
VOID VG4_RndFntDraw( CHAR *Str )
{
  VEC Pos = {0, 0, 0};

  while (*Str != 0)
  {
    if (*Str == '\n')
      Pos.X = 0, Pos.Y -= 1;
    else
      if (VG4_RndFntFont.AdvanceX[(BYTE)*Str] != 0)
      {
        VG4_RndPrimDraw(&VG4_RndFntChars[(BYTE)*Str], MatrTranslate(Pos));
        Pos.X += VG4_RndFntFont.AdvanceX[(BYTE)*Str];
      }
    Str++;
  }
} /* End of 'VG4_RndFntDraw' function */

usage:
  VG4_RndMatrView = MatrIdentity();
  VG4_RndMatrVP = VG4_RndMatrProj =
    MatrOrtho(0, (Ani->W - 1) / 30.0, -(Ani->H - 1) / 30.0, 0, -1, 1);

  sprintf(Buf,
    "FPS: %.3f\n"
    "Renderer: %s\n"
    "Vendor: %s\n"
    "Version: %s\n"
    "GLSL ver: %s",
    Ani->FPS, glGetString(GL_RENDERER), glGetString(GL_VENDOR),
    glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
  VG4_RndFntDraw(Buf);
