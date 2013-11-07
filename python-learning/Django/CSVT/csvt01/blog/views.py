# Create your views here.
from django.http import HttpResponse
from django.template import loader,Context
from django.shortcuts import render_to_response

class Person(object):
    def __init__(self, name, age, sex):
        self.name = name
        self.age = age
        self.sex = sex
    def say(self):
        return self.name


def index_1(req):
    return HttpResponse('<html> hello world</html>')

def index_2(req):
    t = loader.get_template('1.html')
    C = Context({})
    return HttpResponse(t.render(C))

def index_3(req):
    return render_to_response('1.html',{'title':'my page', 'user':'sunbo'})

def index_4(req):
    user={'name':'tom', 'age':23, 'sex':'male'}
    return render_to_response('1.html',{'title':'my page', 'user':user})

def index_5(req):
    user = Person('tom',23,'male')
    book_list = ['python', 'java', 'php']
    return render_to_response('1.html',{'title':'my page', 'user':user, 'book_list':book_list})


def index_6(req):
    user={'name':'tom', 'age':23, 'sex':'male'}
    book_list = ['python', 'java', 'php']
    return render_to_response('1.html',{'title':'my page', 'user':user, 'book_list':book_list})


def index(req, go):
    user={'name':'tom', 'age':23, 'sex':'male'}
    book_list = ['python', 'java', 'php']
    return render_to_response('1.html',{'title':'my page', 'user':user, 'book_list':book_list, 'id':go})
