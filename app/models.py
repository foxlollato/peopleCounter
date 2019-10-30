from . import db
from datetime import datetime

class Detect(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    detect_type = db.Column(db.String(10))
    detect_date = db.Column(db.DateTime, nullable=False, default=datetime.now)