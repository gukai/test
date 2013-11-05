from django.db import models

# Create your models here.
class User(models.Model):
    pname = models.CharField(max_length=150)
    sex = models.CharField(max_length=10)
    age = models.IntegerField(blank=True)
    addr = models.CharField(max_length=255)
    
    def __str__ (self):
        return '%s'%(self.name)

