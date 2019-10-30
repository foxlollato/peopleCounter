from flask import Blueprint, render_template, jsonify, request, flash
from flask_login import login_required, current_user
from . import db
from datetime import datetime
from .models import Detect

main = Blueprint('main', __name__)

@main.route('/')
def index():
    return render_template('index.html')

@main.route('/profile')
@login_required
def profile():
    return render_template('profile.html', name=current_user.name)

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


@main.route('/monitor')
@login_required
def monitor():
    entradas = Detect.query.filter_by(detect_type='entrada').count()
    saidas = Detect.query.filter_by(detect_type='saida').count()    
    quantidade =  entradas - saidas    
    return render_template('monitor.html', quantidade=quantidade)

@main.route('/relatorio')
@login_required
def relatorio():
    return render_template('relatorio.html')

@main.route('/relatorio', methods=['POST'])
@login_required
def relatorio_post():
    date_format = '%Y-%m-%dT%H:%M'
    startDate = datetime.strptime(request.form.get('date-start'), date_format)
    endDate = datetime.strptime(request.form.get('date-end'), date_format)
    visitors = db.session.query(Detect).filter(Detect.detect_date.between(startDate, endDate)).all()
    
    if startDate >= endDate:
        flash('Data de fim deve ser mais recente que a data de início.')
        return render_template('relatorio.html')

    if len(visitors) == 0:
        flash('Sem dados no período.')
        return render_template('relatorio.html')

    return render_template('relatorio.html', visitors=visitors)