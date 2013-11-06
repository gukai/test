# Create your views here.
from django.shortcuts import render_to_response
from Django_Pro.Users.models import Users
from django.http import HttpResponseRedirect

def login(request):
    username=request.GET.get('username', None)
    password=request.GET.get('password', None)
    if username is not None:
        userslist=Users.objects.all()
        for users in userslist:
            if users.username == username and users.password == password:
                request.session['username'] = username
                return render_to_response('login.html', {'username':username})
    return render_to_response('login.html')
