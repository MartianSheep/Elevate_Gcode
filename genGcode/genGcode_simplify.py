import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from PIL import Image
from PIL import ImageFilter
import numpy as np
import potrace





class Piture():
    def __init__(self,filepath):
        self.img=mpimg.imread(filepath)
        self.h,self.w,self.c=self.img.shape
        self.pre=self.img
        self.gcode=['G28']
        self.x_max=40
        self.y_max=40
    #----------------------convert to gray scale----------------------------
    def gray_scale(self):
        print('RBG to gray scale...')
        gray = np.ones(self.img.shape) # new array for gray scale
        for i in range(self.h):
            for j in range(self.w):
                Y = (0.3*self.img[i,j,0]+0.59*self.img[i,j,1]+0.11*self.img[i,j,2])/255
                # print(Y)
                gray[i,j]=np.array([Y,Y,Y])
        self.pre=np.abs(gray-1)
        return gray
    #-----------------------------------------------------------------------

    #-----------------------Show the image on the screen---------------------------
    def show(self):
        plt.imshow(self.pre)
        plt.axis('off')
        plt.show()
    #------------------------------------------------------------------------

    #-----------------------Save the image---------------------------
    def saveImg(self, output):
        plt.imshow(self.pre)
        plt.axis('off')
        plt.imsave(output + '.jpg', self.pre)
        print('Save ' + output + '.jpg')
    #------------------------------------------------------------------------

    #-----------------------Generate Gcode---------------------------
    def gen_gcode(self):
        print('generate gcode...')
        # bmp=potrace.Bitmap(self.pre[:,:]) # binary fill
        bmp=potrace.Bitmap(self.pre[:,:,0])
        path=bmp.trace()
        flag = 0
        for curve in path:
            
            ratio=self.x_max/max(self.w,self.h) #normalize for drawing machine
            self.gcode.append('M280 P0 S60') #抬筆
            self.gcode.append('G0 X%.4f Y%.4f'%(curve.start_point[0]*ratio,curve.start_point[1]*ratio)) #移動到起始點
            self.gcode.append('M280 P0 S0') #下筆
            for segment in curve:
                # print(segment)
                if segment.is_corner:
                    self.gcode.append('G1 X%.4f Y%.4f'%(segment.c[0]*ratio,segment.c[1]*ratio)) #畫至corner的轉角點
                    self.gcode.append('G1 X%.4f Y%.4f'%(segment.end_point[0]*ratio,segment.end_point[1]*ratio)) #畫至corner的終點
                else:
                    self.gcode.append('G1 X%.4f Y%.4f'%(segment.end_point[0]*ratio,segment.end_point[1]*ratio)) #畫至Bezier segment的終點
        self.gcode.append('M280 P0 S60') #抬筆
        return self.gcode
    #------------------------------------------------------------------------
    
    #-----------------------Save Gcode---------------------------
    def save_gcode(self):
        with open('output.txt','w') as f:
            for i in range(len(self.gcode)):
                f.write('%s\n'%self.gcode[i])
    #--------------------------------------------------------------------

    #---------------------------convert to binary image---------------------
    def binary_image(self,threshold):
        print('converting to binary image...')
        self.pre[self.pre[:,:,0]>threshold] = np.array([1,1,1])
        self.pre[self.pre[:,:,0]<=threshold] = np.array([0,0,0])
        return self.pre
    #-----------------------------------------------------------------------------
if __name__=='__main__':
    pic=Piture('img/bear.jpg') #輸入圖片的路徑
    pic.gray_scale()
    pic.binary_image(0.75)
    pic.show()
    gcode=pic.gen_gcode()
    pic.save_gcode()

