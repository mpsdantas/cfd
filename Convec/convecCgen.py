import cgen as c

# Função para ir concatenando as strings.
def append(strOriginal, concatString):
    strOriginal = str(strOriginal)
    concatString = str(concatString)
    return strOriginal + '\n' + concatString;

# Código de saída
CodeOutput = '';

# String temporaria que recebe os valores.

# INÍCIO BLOCO DE DECLARAÇÃO DE VARIAVEIS GLOBAIS
tempString = c.Assign('int ny', '2')
tempString = append(tempString, c.Assign('int nx', '80'))
tempString = append(tempString, c.Assign('int nt', '100'))
tempString = append(tempString, c.Assign('double nx', '2.0 / (nx + 1.0)'))
tempString = append(tempString, c.Assign('double dy', '2.0 / (ny + 1.0)'))
tempString = append(tempString, c.Assign('double sigma', '0.2'))
tempString = append(tempString, c.Assign('double dt', 'sigma * dx'))
# FIM BLOCO DE DECLARAÇÃO DE VARIAVEIS GLOBAIS

# SALVANDO O VALOR NA STRING PRINCIPAL DE SAÍDA
CodeOutput = tempString;

# INÍCIO BLOCO DE INCLUDES E DEFINES
tempString = c.Define("OPS_2D", '')
tempString = append(tempString, c.Include('ops_seq.h', system=True))
tempString = append(tempString, c.Include('iostream', system=True))  
tempString = append(tempString, c.Include('fstream', system=True)) 
tempString = append(tempString, c.Include('convec.h', system=False)) 
tempString = append(tempString, c.Value('using namespace std', ''))
# FIM BLOCO DE INCLUDES

CodeOutput = append(CodeOutput, tempString)

temp = c.FunctionDeclaration(c.Value("", "ops_init"), [c.Value("", "argc"), c.Value("char", "argv"),c.Value("", "1")])
# Array para salvar as operações do Main
blockMain = []
blockMain.append(temp)

print(teste)
func = c.FunctionBody(
    c.FunctionDeclaration(c.Value("int", "main"), [c.Value("int", "argc"), c.Pointer(c.Pointer(c.Value("char", "argv"))) ]),
    c.Block(blockMain)
    )

#print(func)

#print(CodeOutput)