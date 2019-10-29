from flask import Blueprint, render_template, jsonify, request
from . import db
from .models import Detect
main = Blueprint('main', __name__)

@main.route('/entrada')
def entrada():
    detect = Detect(detect_type='entrada')
    db.session.add(detect)
    db.session.commit()
    return jsonify({'Visitantes': 'entrou'})


@main.route('/saida')
def saida():
    detect = Detect(detect_type='saida')
    db.session.add(detect)
    db.session.commit()        
    return jsonify({'Visitantes': 'saiu'})


@main.route('/')
def index():
    visitors = Detect.query.all()

    entradas = Detect.query.filter_by(detect_type='entrada').count()
    saidas = Detect.query.filter_by(detect_type='saida').count()
    
    quantidade =  entradas - saidas

    return render_template('index.html', visitors=visitors, quantidade=quantidade)