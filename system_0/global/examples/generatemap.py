from PIL import Image, ImageFilter

scale = 8

#Read image
im = Image.open( 'twoRoomsCropped.pgm' )

#Display image
im.show()

pix = im.load()
(x1, y1, x2, y2) = im.getbbox() 
print "x1 = %d  y1 = %d    x2 = %d  y2 = %d" % (x1, y1, x2, y2)

length = x2 / scale - 1
width = y2 / scale - 1

print "length = %d  width = %d" % (length, width)

fo = open("dimension.txt", "w")
fo.write("%d\n" % length)
fo.write("%d" % width)
fo.close()

img = Image.new( 'RGB', (x2,y2), "white") # create a new black image
pixels = img.load() # create the pixel map

fo = open("obstacle.txt", "w")
for count1 in range(0, length):
   for count2 in range(0, width):
       pixels[count1*scale + scale,count2 *scale + scale] = 100
       obstacle_flag = 0;
       for x in range (count1*scale, count1*scale + scale):
           for y in range (count2*scale, count2*scale + scale):
               occ = (255 - pix[x,y]) / 255.0
               #fo.write("%f\n" % occ) 
               if occ > 0.197:
               #if occ > 0.75:
                   obstacle_flag = 1
       if obstacle_flag == 1:
           fo.write("%d %d\n" % (count1, count2))
           for x in range (count1*scale, count1*scale + scale):
               for y in range (count2*scale, count2*scale + scale):
                   pixels[x, y] = 255
fo.close()

count1 = 13
count2 = 30 
for x in range (count1*scale, count1*scale + scale):
    for y in range (count2*scale, count2*scale + scale):
        pixels[x, y] = 100
		
img.show()
