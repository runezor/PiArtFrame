from decimal import *
import random
from tqdm import tqdm

class Mandelbrot:
    def __init__(self, w = Decimal(4), h = Decimal(2), x = Decimal(-1), y = Decimal(0)):
        self.w = w
        self.h = h
        self.x = x
        self.y = y
        self.rendered = None
        self.rendered_res_x = 0
        self.rendered_res_y = 0

    def mandel_point(self, C_x, C_y, iter):
        Z_x = C_x
        Z_y = C_y
        for i in range(0, iter):
            Z_x_old = Z_x
            Z_x = Z_x * Z_x - Z_y * Z_y + C_x
            Z_y = 2 * Z_x_old * Z_y + C_y
            if (Z_x ** 2 + Z_y ** 2) > 4:
                return 1
        return 0

    def render(self, res_x, res_y):
        # Approximation for number of iterations
        iter = int(50 + max(0,-Decimal.log10(self.w)) * 100)

        # Updates precision
        getcontext().prec = int(max(0,-Decimal.log10(self.w))+8)

        columns = []

        for y_offset_i in tqdm(range(res_y, 0, -1)):
            row = []
            for x_offset_i in range(0, res_x):
                p_x = self.x - self.w / Decimal(2) + Decimal(x_offset_i) / Decimal(res_x) * self.w
                p_y = self.y - self.h / Decimal(2) + Decimal(y_offset_i) / Decimal(res_y) * self.h

                row += [self.mandel_point(p_x, p_y, iter)]
            columns += [row]


        self.rendered_res_x = res_x
        self.rendered_res_y = res_y
        self.rendered = columns

    def get_render(self):
        return self.rendered

    def is_area_uniform(self, x_offset, y_offset, w, h, w_div, h_div, w_start, h_start):
        first_point = self.rendered[int(y_offset) + int(h / h_div) * h_start][int(x_offset) + int(w / w_div) * w_start]
        for x in range(0, int(w / w_div)):
            for y in range(0, int(h / h_div)):
                if first_point != self.rendered[int(y_offset) + int(h / h_div) * h_start + y][
                    int(x_offset) + int(w / w_div) * w_start + x]:
                    return False
        return True

    def get_uniformness_of_area(self, w, h, x_offset, y_offset, w_div, h_div):
        uniformness = 0
        for w_start in range(w_div):
            for h_start in range(h_div):
                if self.is_area_uniform(x_offset, y_offset, w, h, w_div, h_div, w_start, h_start):
                    uniformness += 1
        return uniformness

    def zoom_on_interesting_area(self):
        choices = []
        # Upper left
        uniformness = self.get_uniformness_of_area(self.rendered_res_x / 2, self.rendered_res_y / 2, 0, 0, 2, 2)
        choices += [(self.x-self.w/4, self.y+self.h/4, uniformness)]
        # Upper right
        uniformness = self.get_uniformness_of_area(self.rendered_res_x / 2, self.rendered_res_y / 2, self.rendered_res_x / 2, 0, 2, 2)
        choices += [(self.x+self.w/4, self.y+self.h/4, uniformness)]
        # Lower left
        uniformness = self.get_uniformness_of_area(self.rendered_res_x / 2, self.rendered_res_y / 2, 0, self.rendered_res_y / 2, 2, 2)
        choices += [(self.x-self.w/4, self.y-self.h/4, uniformness)]
        # Lower right
        uniformness = self.get_uniformness_of_area(self.rendered_res_x / 2, self.rendered_res_y / 2, self.rendered_res_x / 2, self.rendered_res_y / 2, 2, 2)
        choices += [(self.x + self.w / 4, self.y - self.h / 4, uniformness)]

        self.w = self.w / 2
        self.h = self.h / 2

        # Filter out completely uniform squares
        choices = [x for x in choices if x[2]<4]
        # Filter out squares that have 2 or more uniform squares
        less_uniform_choices = [x for x in choices if x[2]<3]
        if len(less_uniform_choices) != 0:
            self.x, self.y, u = random.choice(less_uniform_choices)
        else:
            self.x, self.y, u = random.choice(choices)
