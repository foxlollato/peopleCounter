from . import db
from flask_login import UserMixin
from datetime import datetime

class Detect(db.Model):
    __table_args__ = {'extend_existing': True}
    id = db.Column(db.Integer, primary_key=True)
    detect_type = db.Column(db.String(10))
    detect_date = db.Column(db.DateTime, nullable=False, default=datetime.now)

class User(UserMixin, db.Model):
    __table_args__ = {'extend_existing': True}
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(100), unique=True)
    password = db.Column(db.String(32))
    name = db.Column(db.String(128))