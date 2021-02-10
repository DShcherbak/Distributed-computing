import math
import matplotlib.pyplot as plotter
import numpy


def read_list_of_values(input_file):
    f = open(input_file)
    text = f.read()
    return [float(i) for i in text.split(sep=' ')]


def break_interval(start, end, N):
    return [i * (end/N) for i in range(N)]


def absolute_Fourier(y, k):
    N = len(y)
    val = complex(0,0)
    for i in range(N):
        fi = (-2*math.pi*k*i)/N + 5
        val += y[i] * complex(math.cos(fi), math.sin(fi))
    return abs(val / N)


def find_maximums(x, values):
    result = [(x[i], values[i+1] - values[i]) for i in range(len(values)-1)]
    maxs = []
    for i in range((len(result) // 2) - 1):
        if result[i][1] > 0 and result[i + 1][1] < 0 \
                and abs(result[i + 1][1] * result[i][1]) > 1:
            maxs.append(result[i][0])
    return maxs

def Functional(A, f, x):
    sin_segment = 0
    i = 3
    while (i - 3) < len(maximums):
        sin_segment += A[i] * math.sin(2* math.pi * f[i - 3] * x)
        i += 1
    sin_segment += A[i]
    return A[0] * pow(x, 3) + A[1] * pow(x, 2) + A[2] * x + sin_segment




def calculateMatrix(W, matrix, functions):
    for line_id in range(len(matrix)):
        line = numpy.zeros(6)
        for time in range(0, 500):
            t = 0.01 * time
            Wi = numpy.copy(W[time])
            Wi = numpy.multiply(Wi, functions[line_id](t))
            line = numpy.add(line, Wi)
        matrix[line_id] = numpy.copy(line)

def correction(x):
    for i in range(len(x)):
        x[i] *= (-1)
    return x

if __name__ == "__main__":
    input_file = "f3.txt"
    T = 5
    y = read_list_of_values(input_file)
    N = len(y)
    x = break_interval(0,T, N)
    plotter.plot(x, y)
    plotter.show()

    module_Fourier = [absolute_Fourier(y,i) for i in range(N)]
    plotter.plot(range(N), module_Fourier)
    plotter.show()

    maximums = list(map((lambda x : x / 5 + 0.2) , find_maximums(range(N), module_Fourier)))
    print("Frequencies of local maximums: "
          + str(list(map(lambda x: str(x) + " Hz", maximums))))

    matrix = numpy.zeros((5, 6))
    W = numpy.zeros((len(y), 6))
    functions = [lambda t: t ** 3, lambda t: t ** 2, lambda t: t, lambda t: math.sin(20 * math.pi * t), lambda t: 1]

    for i in range(0, len(y)):
        t = 0.01 * i
        for j in range(5):
            W[i][j] = functions[j](t)
        W[i][5] = -y[i]

    calculateMatrix(W, matrix, functions)

    b = numpy.copy(matrix[:, - 1])
    A = numpy.copy(matrix[:, : - 1])

    args = correction(numpy.linalg.inv(A).dot(b))
    #print(args)
    print("Coefficients of MNK")
    print("A0 = " + str(args[0]))
    print("A1 = " + str(args[1]))
    print("A2 = " + str(args[2]))
    print("A3 = " + str(args[3]))
    print("A4 = " + str(args[4]))

    Functional_Y = [Functional(args, maximums, i * 0.01) for i in range(N)]

    # plot experemental data
    plotter.plot(range(N), y)

    # plot estimated function
    plotter.plot(range(N), Functional_Y, "#FF793d")
    plotter.show()

    plotter.plot(range(N), y)
    plotter.show()

    plotter.plot(range(N), Functional_Y, "#FF793d")
    plotter.show()


